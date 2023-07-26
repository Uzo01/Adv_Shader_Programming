#include "Scene.h"

Scene::Scene(GLFWwindow* window, std::shared_ptr<InputHandler> H) : 
m_window(window),
m_handler(H)
{
	// Shader
	m_terrainShader = new Shader("..\\shaders\\plainVert.vs", "..\\shaders\\plainFrag.fs", "..\\shaders\\geo.gs", "..\\shaders\\tessCon.tcs", "..\\shaders\\tessEval.tes");
	m_terrainShader->use();
	// Camera & Input
	m_camera = std::make_shared<FirstPersonCamera>(glm::vec3(260, 50, 300));   // xyz argument to set starting position of camera
	m_camera->attachHandler(window, H);
	// Terrain Grid
	m_terrain = std::make_shared<Terrain>();
	dirLight = glm::vec3(0.0, -1.0, 0.0);
	ColLight = glm::vec3(1.0, 1.0, 1.0);
	TerrainCol = glm::vec3(1.0, 0.4, 0.4);
	
	
}

Scene::~Scene()
{
	delete m_terrainShader;
}

void Scene::update(float dt)
{
	m_camera->update(dt); // check for input

	// MVP matrices and uniforms
	// move this to a UBO
	m_projection = glm::perspective(m_camera->getFOV(), (float)SCR_WIDTH / (float)SCR_HEIGHT, NEAR_PLANE, FAR_PLANE);  // values from properties header
	m_view = m_camera->getViewMatrix();
	m_model = glm::mat4(1.0f);
	m_terrainShader->use();
	m_terrainShader->setMat4("projection", m_projection);
	m_terrainShader->setMat4("view", m_view);
	m_terrainShader->setMat4("model", m_model);
	m_terrainShader->setVec3("viewPos", m_camera->getPosition());
	m_terrainShader->setVec3("terrainCol", glm::vec3(0.f, 0.f, 1.0f));
	m_terrainShader->setVec3("ColLight", ColLight);
	m_terrainShader->setVec3("dirLight", dirLight);
	m_terrainShader->setVec3("viewPos", m_camera->getPosition());
	m_terrainShader->setFloat("scale", 100);
	

	m_terrain->render(m_terrainShader);
}



