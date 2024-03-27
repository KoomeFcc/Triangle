#include <functionality.h>
#include <IndexBuffer.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):m_count(count)
{

	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_RendererID); //Bind elements to be drawm
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); 

}

IndexBuffer::~IndexBuffer(){

	glDeleteBuffers(1, &m_RendererID);

}

void IndexBuffer::Bind() const{

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *m_RendererID); //Bind elements to be drawm
	
}

void IndexBuffer::Unbind() const{

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Bind elements to be drawm
	

}
