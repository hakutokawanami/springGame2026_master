#pragma once
class Ground
{
public:
	Ground();
	~Ground();
	void Init(int modelHandle);
	void Draw();

private:
	int m_modelHandle;
};

