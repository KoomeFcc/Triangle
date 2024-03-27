#include <functionality.h>
#include <VertexBuffer.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size){

	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, *m_RendererID); //Bind elements to be drawm
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); 

}

VertexBuffer::~VertexBuffer(){

	glDeleteBuffers(1, &m_RendererID);

}

void VertexBuffer::Bind() const{

	glBindBuffer(GL_ARRAY_BUFFER, *m_RendererID); //Bind elements to be drawm
	
}

void Vertexbuffer::Unbind() const{

	glBindBuffer(GL_ARRAY_BUFFER, 0); //Bind elements to be drawm
	

}
