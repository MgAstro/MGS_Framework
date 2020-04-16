#pragma once

class IndexBuffer
{
private:
	unsigned int m_ID;
	unsigned int m_Count;
public:
	IndexBuffer(unsigned int count, const unsigned int *data);
	~IndexBuffer();
public:
	void Bind() const;
	void Unbind() const;
	unsigned int GetCount() const;
};
