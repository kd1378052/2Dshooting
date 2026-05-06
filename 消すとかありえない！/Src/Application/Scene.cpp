#include "main.h"
#include "Scene.h"
#include"SceneManager.h"


void Scene::Draw2D()
{
	SCENEMANAGER.Draw();
}

void Scene::Update()
{
	//マウスカーソルを消す
	//ShowCursor(false);//非表示なる
	SCENEMANAGER.Update();

	if (GetAsyncKeyState('V') & 0x8000)
	{
		SCENEMANAGER.ChangState(new GameScene());
	}
	if (GetAsyncKeyState('C') & 0x8000)
	{
		SCENEMANAGER.ChangState(new ResultScreen());
	}
	
	if (GetAsyncKeyState('X') & 0x8000)
	{
		SCENEMANAGER.ChangState(new RankingScreen());
	}
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		SCENEMANAGER.ChangState(new Title());
	}
	
}

void Scene::Init()
{
	SCENEMANAGER.ChangState(new Title());
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
