#include "render.h"
#include "background.h"
#include "system.h"

//ARREGLAR DELTAT
float tiempoAnt = clock();

Render::Render(){
	glEnable(GL_DEPTH_TEST);
}


void Render::setupObject(Object* obj)
{

	bufferObject_t bo;
	glGenVertexArrays(1, &bo.abo);
	glBindVertexArray(bo.abo);
	
	
	glGenBuffers(1,&bo.vbo);
	glGenBuffers(1,&bo.ibo);
	if (obj->typeObject == CUBE_OBJ) {
		glGenBuffers(1, &bo.ssbo);

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, bo.ssbo);
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, bo.ssbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER,bo.vbo);			
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,bo.ibo);
	

	if (obj->typeObject == CUBE_OBJ) {
		vertex_t* temp = obj->mesh->vertexList->data();
		float* tiempo = new float(69);
		float* constante = new float(420);

		obj->mesh->vertexFisica;
		for (int i = 0; i < obj->mesh->tamTela * obj->mesh->tamTela; i++) {
			obj->mesh->vertexFisica[i].posicion[0] = temp[i].posicion.x;
			obj->mesh->vertexFisica[i].posicion[1] = temp[i].posicion.y;
			obj->mesh->vertexFisica[i].posicion[2] = temp[i].posicion.z;
			obj->mesh->vertexFisica[i].posicion[3] = temp[i].posicion.w;
			obj->mesh->vertexFisica[i].aceleracion[0] = 0;
			obj->mesh->vertexFisica[i].aceleracion[1] = 0;
			obj->mesh->vertexFisica[i].aceleracion[2] = 0;
			obj->mesh->vertexFisica[i].aceleracion[3] = 0;
			for (int j = 0; j < 8; j++) {
				obj->mesh->vertexFisica[i].vecinosCercanos[j] = temp[i].vecinosCercanos[j];
				//printf("%d %d %d\n",i, j, templist1[i].verticesAdyacentes[j]);
			}
			obj->mesh->vertexFisica[i].control = 0;
		}

		glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * 2 + sizeof(vertexFisico_t) * obj->mesh->tamTela * obj->mesh->tamTela + sizeof(int), &DeltaT, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(float), sizeof(float), constante);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * 2, sizeof(int), &obj->mesh->tamTela);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * 2 + sizeof(int), sizeof(vertexFisico_t) * obj->mesh->tamTela * obj->mesh->tamTela, obj->mesh->vertexFisica);
		
		DeltaT = clock();
	}
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * obj->mesh->vertexList->size(),
		obj->mesh->vertexList->data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * obj->mesh->faceList->size(),
		obj->mesh->faceList->data(), GL_STATIC_DRAW);
	boList[obj->id] = bo;
}

void Render::updateObject(Object* obj) {
	if (obj->typeObject == CUBE_OBJ) {
		DeltaT -= clock();

		DeltaT = -DeltaT / CLOCKS_PER_SEC;
		//printf("%f\n\n", DeltaT);
		float* tiempo = new float(0);
		float* constMuelle = new float(0);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(float), &DeltaT);
		DeltaT = clock();
		glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(float), tiempo);
		glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(float), sizeof(float), constMuelle);
		glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * 2 + sizeof(int), sizeof(vertexFisico_t) * obj->mesh->tamTela * obj->mesh->tamTela, obj->mesh->vertexFisica);
		/*printf("%f %f\n", *tiempo, *constMuelle);
		printf("%d %f %f %f %f %f %f %d %d %d %d %d %d %d %d %d\n", obj->mesh->vertexFisica[ayudapls].control, obj->mesh->vertexFisica[ayudapls].posicion[0]
			, obj->mesh->vertexFisica[ayudapls].posicion[1], obj->mesh->vertexFisica[ayudapls].posicion[2], obj->mesh->vertexFisica[ayudapls].aceleracion[0]
			, obj->mesh->vertexFisica[ayudapls].aceleracion[1], obj->mesh->vertexFisica[ayudapls].aceleracion[2], obj->mesh->vertexFisica[ayudapls].vecinosCercanos[0]
			, obj->mesh->vertexFisica[ayudapls].vecinosCercanos[1], obj->mesh->vertexFisica[ayudapls].vecinosCercanos[2], obj->mesh->vertexFisica[ayudapls].vecinosCercanos[2]
			, obj->mesh->vertexFisica[ayudapls].vecinosCercanos[3], obj->mesh->vertexFisica[ayudapls].vecinosCercanos[4], obj->mesh->vertexFisica[ayudapls].vecinosCercanos[5]
			, obj->mesh->vertexFisica[ayudapls].vecinosCercanos[6], obj->mesh->vertexFisica[ayudapls].vecinosCercanos[7]);
			*/
		ayudapls++;
		if (ayudapls >= obj->mesh->tamTela * obj->mesh->tamTela) {
			ayudapls = 0;
		}
		for (int i = 0; i < obj->mesh->vertexList->size(); i++) {
			obj->mesh->vertexList->at(i).posicion.x = obj->mesh->vertexFisica[i].posicion[0];
			obj->mesh->vertexList->at(i).posicion.y = obj->mesh->vertexFisica[i].posicion[1];
			obj->mesh->vertexList->at(i).posicion.z = obj->mesh->vertexFisica[i].posicion[2];
			obj->mesh->vertexList->at(i).posicion.w = obj->mesh->vertexFisica[i].posicion[3];
		}
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * obj->mesh->vertexList->size(),
			obj->mesh->vertexList->data(), GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * obj->mesh->faceList->size(),
			obj->mesh->faceList->data(), GL_STATIC_DRAW);
	}

}


void Render::drawMesh(Mesh* mesh,glm::mat4 model){


	int numFaces=(int)mesh->faceList->size()/3;
	for(int i=0;i<numFaces;i++)
	{
	glBegin(GL_TRIANGLES);
		glm::vec4 newPos;	
		for(int idV=i*3; idV<(i*3+3); idV++)
		{   
			vertex_t v=mesh->vertexList->data()[mesh->faceList->data()[idV]];
			newPos=proj*view*model*v.posicion;
			glColor3f(v.color.r,v.color.g,v.color.b);
			glVertex3f(newPos.x,newPos.y,newPos.z);
		}
	
	glEnd();
	}
}


void Render::drawObject(Object* obj){
	obj->computeMatrix();
	drawMesh(obj->mesh,obj->getMatrix());	
}




void Render::drawObjectGL4(Object* obj, Scene *scene){
	obj->computeMatrix();
	updateObject(obj);
	
	bufferObject_t bo=boList[obj->id];
	
	glBindVertexArray(bo.abo);
	glBindBuffer(GL_ARRAY_BUFFER, bo.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo.ibo);
	
	if (obj->typeObject == CUBE_OBJ) {
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, bo.ssbo);

		glUseProgram(obj->shader->computeProgramID);
		//glDispatchCompute(ceil(640 / 640), ceil(480 / 480), 1);
		// Dividir Shader en work groups uno por cada particula (SE DEBE CAMBIAR PARA CALCULO SI SE CAMBIA EL TAMAÑO DE TELA)
		glDispatchCompute((unsigned int)obj->mesh->tamTela, (unsigned int)obj->mesh->tamTela, (unsigned int)1);
		

		
	}
	glMemoryBarrier(GL_ALL_BARRIER_BITS);
	glUseProgram(obj->shader->programID);

	unsigned int vpos=0;
	glEnableVertexAttribArray(vpos);
	glVertexAttribPointer(vpos,4,GL_FLOAT,GL_FALSE,sizeof(vertex_t),(void*)offsetof(vertex_t,posicion));

	unsigned int vcolor=1;
	glEnableVertexAttribArray(vcolor);
	glVertexAttribPointer(vcolor,4,GL_FLOAT,GL_FALSE,sizeof(vertex_t),(void*)offsetof(vertex_t,color));

	unsigned int vnorm=2;
	glEnableVertexAttribArray(vnorm);
	glVertexAttribPointer(vnorm,4,GL_FLOAT,GL_FALSE,sizeof(vertex_t),(void*)offsetof(vertex_t,normal));

	unsigned int vtext = 3;
	glEnableVertexAttribArray(vtext);
	glVertexAttribPointer(vtext, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), (void*)offsetof(vertex_t, texCoord));


	
	Light light1 = scene->getLight(0);
	Light light2 = scene->getLight(1);
	
	Camera* cam = scene->getCamera();
	glm::vec4 userPos = cam->camPos();
	//glm::vec4 userPos = glm::vec4(0, 0, 6.0, 1);

	
	glUniformMatrix4fv(0,1,GL_FALSE,&(proj*view*obj->getMatrix())[0][0]);	

	glm::mat4 matT = glm::translate(glm::mat4(1.0f), obj->position);
	matT = glm::rotate(matT, obj->rotation.x, glm::vec3(1.0f, 0, 0));
	matT = glm::rotate(matT, obj->rotation.y, glm::vec3(0, 1.0f, 0));
	matT = glm::rotate(matT, obj->rotation.z, glm::vec3(0, 0, 1.0f));

	glUniformMatrix4fv(1,1,GL_FALSE,&(matT)[0][0]);	
	glUniform4fv(2,1, &light1.lightPos[0]);
	glUniform4fv(7,1, &light2.lightPos[0]);
	glUniform4fv(3,1,&userPos[0]);

	int textureUnit = 0;
	glUniform1i(4,textureUnit);
	obj->mesh->tex->bind(textureUnit);


	glm::vec2 scroll = glm::vec2(0,0);
	if (obj->typeObject == BACKGROUND_OBJ) {
		Background* aux = (Background*)obj;
		scroll = aux->scroll;
	}
	glUniform1f(5, 1.0f);
	glUniform2fv(6,1, &scroll[0]);

	
	//glEnable(GL_ALPHA_TEST);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*
	if(obj->typeObject == CUBE_OBJ)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	*/
	
	glDrawElements(GL_TRIANGLES, obj->mesh->faceList->size(), GL_UNSIGNED_INT,nullptr);
	
}


void Render::drawScene(Scene* scene)
{

	Camera* cam=scene->getCamera();
	std::map<int,Object*> *addedObjList=scene->addedObjList;
	
	for(auto it=addedObjList->begin();
            it!=addedObjList->end();
            it++)
    {

        setupObject(it->second);
    }
    
	cam->computeMatrix();
	view=cam->getMatrix();
	proj=cam->getProjectionMatrix();
	std::map<int,Object*>* objList=scene->getObjList();	
	
	for(auto it=objList->begin();
		it!=objList->end();
		it++)
	{
		drawObjectGL4(it->second, scene);
	}

}









