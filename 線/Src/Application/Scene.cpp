#include "main.h"
#include "Scene.h"
#include"SceneMenager.h"


void Scene::Draw2D()
{
	SCENEMANAGER.Draw();
}

void Scene::Update()
{
	SCENEMANAGER.Update();

	if (GetAsyncKeyState('A') & 0x8000)
	{
		SCENEMANAGER.ChangState(new SelectionScreen());
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		SCENEMANAGER.ChangState(new ResultScreen());
	}
	
	if (GetAsyncKeyState('S') & 0x8000)
	{
		SCENEMANAGER.ChangState(new RankingScreen());
	}
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		SCENEMANAGER.ChangState(new TutorialScreen());
	}
	if (GetAsyncKeyState('X') & 0x8000)
	{
		SCENEMANAGER.ChangState(new GameScreen());
	}
	
}

void Scene::Init()
{
	SCENEMANAGER.ChangState(new GameScreen());
}

void Scene::Release()
{
	// 画像の解放処理
	charaTex.Release();
}

void Scene::ImGuiUpdate()
{
	return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
	}
	ImGui::End();
}
