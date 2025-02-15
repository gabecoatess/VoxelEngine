// TimeUtility.h

#ifndef TIMEUTILITY_H
#define TIMEUTILITY_H

class TimeUtility
{
public:
	static TimeUtility& GetInstance();

	void Initialize();

	void Update();

	int GetFramesPerSecond() const;
	float GetDeltaTime() const;

	void Destroy();

private:
	TimeUtility();
	~TimeUtility();

	TimeUtility(const TimeUtility&) = delete;
	TimeUtility& operator=(const TimeUtility&) = delete;

	int framesPerSecond;
	float deltaTime;
	float lastFrameTime;
	float frameTimer;
	int frameCount;
};

#endif