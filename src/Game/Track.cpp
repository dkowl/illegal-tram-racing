#include "Track.h"

const float Track::SEGMENT_LENGTH = 0.01f; //meters

const float Track::MIN_TURN_TOTAL_ANGLE = 10; //degrees
const float Track::MAX_TURN_TOTAL_ANGLE = 90;

const float Track::MIN_TURN_ANGULAR_SPEED = 0.5f; //degrees per meter
const float Track::MAX_TURN_ANGULAR_SPEED = 5;

const float Track::MIN_STRAIGHT_SEGMENT_LENGTH = 10; //meters
const float Track::MAX_STRAIGHT_SEGMENT_LENGTH = 100;

const float Track::TRACK_WIDTH = 2.5f;
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

glm::mat3& Track::SegmentVertexPositions(int i) const
{

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
	glm::vec3 deltaVector;
	if (segments.empty()) deltaVector = glm::vec3(0, 0, -1);
	else deltaVector = segments[segments.size() - 2].deltaVector;
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
	glm::mat4 rotationMatrix = glm::rotate(rotationMatrix, glm::radians(angularSpeed), glm::vec3(0, 1, 0));
	deltaVector4 = rotationMatrix * deltaVector4;
	for (int i = 0; i < segmentCount; i++)
	{
		AddSegment(deltaVector4);
	}
	std::cout << "Turn segment generated!\n	length: " << TurnLength(totalAngle, angularSpeed)
		<< "\n	segmentCount: " << segmentCount
		<< "\n	totalAngle: " << totalAngle
		<< "\n	angularSpeed: " << angularSpeed
		<< "\n\n";
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

float Track::TurnLength(float totalAngle, float angularSpeed)
{
	return totalAngle / angularSpeed;
}

float Track::MinTurnLength()
{
	return TurnLength(MIN_TURN_TOTAL_ANGLE, MAX_TURN_ANGULAR_SPEED);
}
