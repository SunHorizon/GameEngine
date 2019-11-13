#include "Mesh.h"


Mesh::Mesh(SubMesh subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), shaderProgram(0)
{
	shaderProgram = shaderProgram_;
	subMesh = subMesh_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	OnDestroy();
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);

	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid*>(0));

	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//TEXTURE
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texCoords));

	//COLOUR
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, colour));


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projLoc = glGetUniformLocation(shaderProgram, "proj");
	TextureLoc = glGetUniformLocation(shaderProgram, "inputTexture");

	viewPosition = glGetUniformLocation(shaderProgram, "CameraPosition");
	lighPosition = glGetUniformLocation(shaderProgram, "light.lighPostion");
	lighAmbient = glGetUniformLocation(shaderProgram, "light.ambient");
	lighDiffuse = glGetUniformLocation(shaderProgram, "light.diffuse");
	lighColor = glGetUniformLocation(shaderProgram, "light.lightColor");

	diffuseMapLoc = glGetUniformLocation(shaderProgram, "material.diffuceMap");
	shinninesLoc = glGetUniformLocation(shaderProgram, "material.shininess");
	transparencyLoc = glGetUniformLocation(shaderProgram, "material.transparency");
	ambientLoc = glGetUniformLocation(shaderProgram, "material.ambient");
	diffuseLoc = glGetUniformLocation(shaderProgram, "material.diffuse");
	specLoc; glGetUniformLocation(shaderProgram, "material.specular");
}

void Mesh::Render(Camera* camera, std::vector<glm::mat4> &instance_)
{
	glUniform1i(diffuseMapLoc, 0);
	glActiveTexture(GL_TEXTURE);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuceMap);

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->GetView()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->GetPerspective()));


	/*glUniform3fv(viewPosition, GL_FALSE, glm::value_ptr(camera->getPosition()));
	glUniform3fv(lighPosition, GL_FALSE, glm::value_ptr(camera->getLightSource()[0]->getPosition()));
	glUniform1f(lighAmbient,camera->getLightSource()[0]->getAmbient());
	glUniform1f(lighDiffuse,camera->getLightSource()[0]->getDiffuse());
	glUniform3fv(lighColor, GL_FALSE, glm::value_ptr(camera->getLightSource()[0]->GetlightColor()));*/


	glUniform3f(viewPosition, camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
	glUniform3f(lighPosition, camera->getLightSource()[0]->getPosition().x, camera->getLightSource()[0]->getPosition().y, camera->getLightSource()[0]->getPosition().z);
	glUniform1f(lighAmbient, camera->getLightSource()[0]->getAmbient());
	glUniform1f(lighDiffuse, camera->getLightSource()[0]->getDiffuse());
	glUniform3f(lighColor,camera->getLightSource()[0]->GetlightColor().x, camera->getLightSource()[0]->GetlightColor().y, camera->getLightSource()[0]->GetlightColor().z);

	glUniform1i(shinninesLoc, subMesh.material.shininess);
	glUniform1i(transparencyLoc, subMesh.material.transparency);

	glUniform3f(ambientLoc, subMesh.material.ambient.x, subMesh.material.ambient.y, subMesh.material.ambient.z);
	glUniform3f(diffuseLoc, subMesh.material.diffuse.x, subMesh.material.diffuse.y, subMesh.material.diffuse.z);
	glUniform3f(specLoc, subMesh.material.specular.x, subMesh.material.specular.y, subMesh.material.specular.z);


	glBindVertexArray(VAO);
	for(int i = 0; i < instance_.size(); i++)
	{
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instance_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Mesh::OnDestroy()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	subMesh.vertexList.clear();
	subMesh.meshIndices.clear();
}

