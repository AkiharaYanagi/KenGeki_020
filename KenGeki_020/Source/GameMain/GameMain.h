//=================================================================================================
//
// ゲームメイン　ヘッダ
//			ゲーム内容における主となる挙動を記述する。ヘッダのみ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//ゲーム内容ヘッダファイルのインクルード
#include "Scene.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//ゲームメインクラス
//	class GameMain	: public TASK_VEC
	class GameMain	: public GameMainBase
	{
#define GAME_MAIN_ONLY_TEST		0
#if GAME_MAIN_ONLY_TEST
		//ゲームメインのみのテスト
		std::shared_ptr < GameTask > m_pTask;
#else
		//ゲームに用いるオブジェクトクラス
		std::shared_ptr < SceneManager > m_pTask;
#endif	//GAME_MAIN_TEST

	public:
		GameMain()
		{
			Make ();				//タスク生成
			AddpTask ( m_pTask );	//タスクの追加
		}
		GameMain(const GameMain& rhs) = delete;
		~GameMain () {}

		//タスク生成
		void Make ()
		{
#if GAME_MAIN_ONLY_TEST
			m_pTask = std::make_shared < GameTask > ();
#else
			m_pTask = std::make_shared < SceneManager > ();
#endif	//GAME_MAIN_TEST
		}
	};


	using UP_GameMain = std::unique_ptr < GameMain >;


}	//namespace GAME

