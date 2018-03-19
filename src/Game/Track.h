#pragma once

#include <vector>
#include <iostream>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Track
{
public:
	struct Segment
	{
		glm::vec3 position;
		glm::vec3 deltaVector;

		explicit Segment(const glm::vec3 &position);
		glm::vec3 NextPosition() const;
	};

	static const float SEGMENT_LENGTH; //meters

	static const float MIN_TURN_TOTAL_ANGLE; //degrees
	static const float MAX_TURN_TOTAL_ANGLE;

	static const float MIN_TURN_ANGULAR_SPEED; //degrees per meter
	static const float MAX_TURN_ANGULAR_SPEED;

	static const float MIN_STRAIGHT_SEGMENT_LENGTH; //meters
	static const float MAX_STRAIGHT_SEGMENT_LENGTH;

	static const float TRACK_WIDTH;
	static const float TRACK_GAUGE;

private:
	std::vector<Segment> segments;

public:
	explicit Track(float length);

	unsigned int SegmentCount() const;

	glm::mat3& SegmentVertexPositions(int i) const;

private:
	void GenerateSegments(float length);
	void GenerateStraightSegment(float length);
	void GenerateTurnSegment(float totalAngle, float angularSpeed);

	void AddSegment(glm::vec3 deltaVector);

	static float TurnLength(float totalAngle, float angularSpeed);
	static float MinTurnLength();
};