﻿//=================================================================================================
//
//	FtgMain ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "FtgMain.h"
#include "../GameMain/G_Ftg.h"
#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	FtgMain::FtgMain ()
	{
		//戦闘
		m_fighting = std::make_shared < Fighting > ();
		AddpTask ( m_fighting );

		//ポーズメニュ
		m_pauseMenu = std::make_shared < PauseMenu > ();
		AddpTask ( m_pauseMenu );

#if 0

		//ロード中
		m_rectLoad = make_shared < PrmRect > ();
		m_rectLoad->SetSize ( VEC2 ( 1280, 960 ) );
		m_rectLoad->SetPos ( VEC2 ( 0, 0 ) );
		m_rectLoad->SetAllColor ( 0xff000000 );
		m_rectLoad->SetZ ( Z_FADE );

		m_rectLoad->Load ();
		m_rectLoad->Move ();

//		m_rectLoad->SetFadeOut ( 10 );	//SetFadeOut()は0xffffffff->0x00ffffffなので白くなる
		m_rectLoad->SetFade ( 3, _CLR(0xff000000), _CLR(0x00000000UL) );	//開始値、目標値を手動設定

		AddpTask ( m_rectLoad );
		GRPLST_INSERT_MAIN ( m_rectLoad );
		m_wait = 0;

		
		m_NowLoading = make_shared < GrpStr > ();
		m_NowLoading->SetStr ( _T ( "Now Loading..." ) );
		m_NowLoading->SetPos ( VEC2 ( 1000, 915 ) );
		m_NowLoading->Load ();
		m_NowLoading->Move ();
		m_NowLoading->SetZ ( Z_FADE - 0.01f );
		AddpTask ( m_NowLoading );
		GRPLST_INSERT_MAIN ( m_NowLoading );
#endif // 0


		//----------------------------------------------------
		//@info コンストラクタでshared_from_this()を用いない
	}

	FtgMain::~FtgMain ()
	{
	}

	void FtgMain::ParamInit ()
	{
		m_fighting->ParamInit ( GetpParam () );
	}

	void FtgMain::Load ()
	{
		//戦闘共通
		G_Ftg::inst()->Init ();

		//遷移先指定にthisを保存
		Scene::SetwpThis ( shared_from_this () );

		//Menu用にthisを保存
		m_pauseMenu->SetwpParentScene ( shared_from_this () );

#if 0

		//BGM
		P_Param pParam = Scene::GetpParam ();
		BGM_ID bgm_id = pParam->Get_BGM_ID ();
		SND_STOP_ALL_BGM ();
		SND_PLAY_LOOP_BGM ( BGM_ID_TO_NAME [ bgm_id ] );
#endif // 0


		Scene::Load ();
	}


	void FtgMain::Move ()
	{
#if 0
		//NowLoading終了
		if ( m_rectLoad->GetFadeTimer () == 0 )
		{
			m_NowLoading->SetValid ( F );
		}
#endif // 0

		//メニュポーズ中
		if ( m_pauseMenu->MenuCheck () )
		{
			return;
		}

		//デモ リスタート
		if ( WND_UTL::AscKey ( '0' ) )
		{
			m_fighting->DemoRestart ();
		}

#if 0
		//トレーニングリセット
		bool p1Reset = CFG_PUSH_KEY ( P1_BTN7 );
		bool p2Reset = CFG_PUSH_KEY ( P2_BTN7 );
		bool sysReset = WND_UTL::AscKey ( VK_BACK );
		if ( p1Reset || p2Reset || sysReset )
		{
			m_fighting->TrainingRestart ();
		}
#endif // 0

		//通常動作
		Scene::Move ();

	}

	//状態遷移
	P_GameScene FtgMain::Transit ()
	{
		//終了チェック
		if ( m_fighting->IsEnd () )
		{
			//BGM終了
			SND_STOP_ALL_BGM ();

			//シーン遷移
			Scene::Transit_Result ();
		}

		//引分終了
		if ( m_fighting->IsDrawEnd () )
		{
			//BGM終了
			SND_STOP_ALL_BGM ();

			//シーン遷移
			Scene::Transit_CharaSele ();
		}

		return Scene::Transit ();
	}
	
}	//namespace GAME

