#include "Track.h"

const float Track::SEGMENT_LENGTH = 1.f; //meters

const float Track::MIN_TURN_TOTAL_ANGLE = 10; //degrees
const float Track::MAX_TURN_TOTAL_ANGLE = 90;

const float Track::MIN_TURN_ANGULAR_SPEED = 0.2f; //degrees per meter
const float Track::MAX_TURN_ANGULAR_SPEED = 2;

const float Track::MIN_STRAIGHT_SEGMENT_LENGTH = 10; //meters
const float Track::MAX_STRAIGHT_SEGMENT_LENGTH = 50;

const float Track::TRACK_WIDTH = 2.9f;
const float Track::TRACK_GAUGE = 1.435f;

Track::Segment::Segment(const glm::vec3 &position):
	position(position)
{

}

glm::vec3 Track::Segment::NextPosition() const
{
	return position + deltaVector;
}

Track::Track(float length)
{
	GenerateSegments(length);
}

unsigned Track::SegmentCount() const
{
	return segments.size();
}

std::vector<glm::vec3> Track::SegmentVertexPositions(int i) const
{
	const glm::vec3 segmentDirection = SegmentDirection(i);
	const glm::vec3 position = segments[i].position;
	const glm::vec3 direction = glm::normalize(glm::vec3(segmentDirection.z, 0, -segmentDirection.x));
	std::vector<glm::vec3> result{
		position - direction * (TRACK_WIDTH / 2),
		position + direction * (TRACK_WIDTH / 2),
		position + direction * (TRACK_WIDTH * 1.5f)
	};
	return result;
}

std::vector<glm::vec2> Track::SegmentVertexUvs(int i) const
{
	float v = glm::fract((SEGMENT_LENGTH * i) / TRACK_WIDTH);

	std::vector<glm::vec2> result{
		glm::vec2(1, v),
		glm::vec2(0, v),
		glm::vec2(1, v)
	};
	return result;
}

glm::vec3 Track::SegmentDirection(int i) const
{
	if (i < 1) return glm::vec3(0, 0, -1) * SEGMENT_LENGTH;
	else return segments[i - 1].deltaVector;
}

glm::vec3 Track::GetPositionAtDistance(float distance) const
{
	float segmentsTraveled = distance / SEGMENT_LENGTH;
	segmentsTraveled = glm::clamp(float(segmentsTraveled), 0.f, float(SegmentCount() - 1));
	int indexBefore = glm::floor(segmentsTraveled);
	int indexAfter = glm::ceil(segmentsTraveled);
	float lerpRatio = glm::fract(segmentsTraveled);
	return glm::mix(segments[indexBefore].position, segments[indexAfter].position, lerpRatio);
}

std::vector<glm::vec3> Track::GetTramAxisPositions(float distance, float axisDistance) const
{
	std::vector<glm::vec3> result(2);
	
	float lerpRatio = LerpRatio(distance);
	const int mainSegmentIndex = glm::clamp(distance / SEGMENT_LENGTH, 0.f, float(SegmentCount() - 1));

	int resultIndex = 0;
	int lastModifiedResultIndex = -1;
	int backIndex = mainSegmentIndex;
	int frontIndex = mainSegmentIndex;
	while(true)
	{
		if(resultIndex == 0 && frontIndex < SegmentCount() - 1)
		{
			frontIndex++;
			lastModifiedResultIndex = 0;
		}
		else if(resultIndex == 1 && backIndex > 0)
		{
			backIndex--;
			lastModifiedResultIndex = 1;
		}

		float currentDistance = glm::length(segments[frontIndex].position - segments[backIndex].position);
		if(currentDistance > axisDistance)
		{
			if(lastModifiedResultIndex == 0)
			{
				result[0] = GetPosition(frontIndex - 1 + lerpRatio);
				result[1] = GetPosition(backIndex + lerpRatio);
			}
			else 
			{
				result[0] = GetPosition(frontIndex + lerpRatio);
				result[1] = GetPosition(backIndex + lerpRatio);
			}
			//std::cout << "lerpRatio: " << lerpRatio << " front: ";
			//Utils::DisplayVec3(result[0]);
			//std::cout << " back: ";
			//Utils::DisplayVec3(result[1]);
			return result;
		}
		
		resultIndex++;
		resultIndex %= 2;
	}
}

void Track::GenerateSegments(float length)
{
	std::default_random_engine randomEngine;
	const std::uniform_real_distribution<float> turnTotalAngleDist(MIN_TURN_TOTAL_ANGLE, MAX_TURN_TOTAL_ANGLE);
	const std::uniform_real_distribution<float> turnAngularSpeedDist(MIN_TURN_ANGULAR_SPEED, MAX_TURN_ANGULAR_SPEED);
	const std::uniform_int_distribution<int> turnDirectionDist(0, 1); //1 = left, 0 = right;
	const std::uniform_real_distribution<float> straightSegmentLengthDist(MIN_STRAIGHT_SEGMENT_LENGTH, MAX_STRAIGHT_SEGMENT_LENGTH);

	float lengthRemaining = length;

	while (lengthRemaining > MAX_STRAIGHT_SEGMENT_LENGTH)
	{
		const float straightSegmentLength = straightSegmentLengthDist(randomEngine);
		GenerateStraightSegment(straightSegmentLength);
		lengthRemaining -= straightSegmentLength;

		if (lengthRemaining < MinTurnLength()) break;

		int i = 0;
		while (true)
		{
			float turnTotalAngle;
			float turnAngularSpeed;
			if (i > 100)
			{
				turnTotalAngle = MIN_TURN_TOTAL_ANGLE;
				turnAngularSpeed = MAX_TURN_ANGULAR_SPEED;
			}
			else
			{
				turnTotalAngle = turnTotalAngleDist(randomEngine);
				turnAngularSpeed = turnAngularSpeedDist(randomEngine);
			}
			const float turnLength = TurnLength(turnTotalAngle, turnAngularSpeed);
			if (turnLength <= lengthRemaining)
			{
				const bool turnDirectionLeft = turnDirectionDist(randomEngine);
				if (turnDirectionLeft)
				{
					turnTotalAngle *= -1.f;
					turnAngularSpeed *= -1.f;
				}
				GenerateTurnSegment(turnTotalAngle, turnAngularSpeed);
				lengthRemaining -= turnLength;
				break;
			}
			i++;
		}

	}
	GenerateStraightSegment(lengthRemaining);
}

void Track::GenerateStraightSegment(float length)
{
	const int segmentCount = glm::ceil(length / SEGMENT_LENGTH);
	const glm::vec3 deltaVector = SegmentDirection(segments.size() - 1);
	for (int i = 0; i < segmentCount; i++)
	{
		AddSegment(deltaVector);
	}
	std::cout << "Straight segment generated!\n	length: " << length << "\n	segmentCount: " << segmentCount << "\n\n";
}

void Track::GenerateTurnSegment(float totalAngle, float angularSpeed)
{
	const int segmentCount = glm::ceil(TurnLength(totalAngle, angularSpeed) / SEGMENT_LENGTH);
	glm::vec4 deltaVector4 = glm::vec4(segments[segments.size() - 2].deltaVector, 1);
	glm::mat4 rotationMatrix;
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angularSpeed * SEGMENT_LENGTH), glm::vec3(0, 1, 0));
	for (int i = 0; i < segmentCount; i++)
	{
		deltaVector4 = rotationMatrix * deltaVector4;
		AddSegment(deltaVector4);
	}
	/*std::cout << "Turn segment generated!\n	length: " << TurnLength(totalAngle, angularSpeed)
		<< "\n	segmentCount: " << segmentCount
		<< "\n	totalAngle: " << totalAngle
		<< "\n	angularSpeed: " << angularSpeed
		<< "\n\n";*/
}

void Track::AddSegment(glm::vec3 deltaVector)
{
	if(segments.empty())
	{
		segments.emplace_back(Segment(glm::vec3(0)));
		return;
	}
	segments.back().deltaVector = deltaVector;
	segments.emplace_back(Segment(segments.back().NextPosition()));
}

glm::vec3 Track::MovePositionForwardByXSegments(float distance, float x) const
{
	int segmentsTraveled = SegmentsTraveled(distance) + x;
	segmentsTraveled = glm::clamp(float(segmentsTraveled), 0.f, float(SegmentCount() - 1));
	return GetPosition(segmentsTraveled);

}

float Track::SegmentsTraveled(float distance) const
{
	float segmentsTraveled = distance / SEGMENT_LENGTH;
	segmentsTraveled = glm::clamp(float(segmentsTraveled), 0.f, float(SegmentCount() - 1));
	return segmentsTraveled;
}

float Track::SegmentIndex(float distance) const
{
	return glm::floor(SegmentsTraveled(distance));
}

float Track::LerpRatio(float distance) const
{
	return glm::fract(SegmentsTraveled(distance));
}

glm::vec3 Track::GetPosition(float segmentsTraveled) const
{
	segmentsTraveled = glm::clamp(segmentsTraveled, 0.f, float(SegmentCount() - 1));
	int indexBefore = glm::floor(segmentsTraveled);
	int indexAfter = glm::ceil(segmentsTraveled);
	float lerpRatio = glm::fract(segmentsTraveled);
	return glm::mix(segments[indexBefore].position, segments[indexAfter].position, lerpRatio);
}

float Track::TurnLength(float totalAngle, float angularSpeed)
{
	return totalAngle / angularSpeed;
}

float Track::MinTurnLength()
{
	return TurnLength(MIN_TURN_TOTAL_ANGLE, MAX_TURN_ANGULAR_SPEED);
}
