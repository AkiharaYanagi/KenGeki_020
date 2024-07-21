//=================================================================================================
//
//	Fighting ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Fighting.h"
#include "FtgConst.h"	


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	Fighting::Fighting ()
	{
		//------------------------------------------------
		//背景
		m_bg = std::make_shared < BG > ();
		AddpTask ( m_bg );


		m_grp = std::make_shared < GameGraphic > ();
		m_grp->AddTexture ( U"ef_004.png" );
		m_grp->SetPos ( VEC2 ( 200, 300 ) );
//		AddpTask ( m_grp );

		//=====================================================
		//キャラ相互処理
		//=====================================================
		m_mutualChara = std::make_shared < MutualChara > ();
		AddpTask ( m_mutualChara );

#if 0
		//=====================================================
		//デモ
		m_demoActor = make_shared < FtgDemoActor > ();		m_demoActor->Load ();
		m_demoActor->SetpMutualChara ( m_mutualChara );
		AddpTask ( m_demoActor );

		//Debug用　開始デモをスキップ切替
#define DEMO_ON		0
#if DEMO_ON
		m_demoSkip = F;
#else
		m_demoSkip = T;
#endif // DEMO_ON

		//=====================================================
		//画面共通グラフィック処理
		m_pFtgGrp = make_shared < FtgGrp > ();
#endif // 0
	}

	Fighting::~Fighting ()
	{
	}


	void Fighting::ParamInit ( P_Param pParam )
	{
		m_mutualChara->ParamInit ( pParam );
	}

	void Fighting::Load ()
	{
#if 0
		m_mutualChara->SetpFtgGrp ( m_pFtgGrp );
#endif // 0
		TASK_LST::Load ();
	}

	void Fighting::Init ()
	{
		//基準 初期化
		TASK_LST::Init ();

#if 0
		//初期化後
	
		//デモスキップ
		if ( m_demoSkip )
		{
			m_demoActor->StartFighting ();
		}
		else
		{
			m_demoActor->StartGreeting ();
		}
#endif // 0
	}


	void Fighting::Move ()
	{
		m_mutualChara->Conduct ();

#if 0
		//--------------------------
		//デモ分岐
		m_demoActor->Do ();

		//--------------------------
		//両者処理


		//暗転時は通常処理しない
//		if ( m_bg->IsBlackOut () )
		if ( m_pFtgGrp->GetBlackOut () )
		{
			//入力のみ
			m_mutualChara->Conduct_InStop ();
		}
		else
		{
			//暗転以外のとき、通常処理
			m_mutualChara->Conduct ();
		}


		//--------------------------
		//共通グラフィック処理
		Grp ();

		//--------------------------
#endif // 0
		TASK_LST::Move ();
	}

#if 0
	void Fighting::TrainingRestart ()
	{
		m_pFtgGrp->Init ();
		m_bg->Init ();
		m_demoActor->StartFighting ();
		m_mutualChara->TrainingInit ();
	}

	

	//=============================================================
	//	内部関数
	//=============================================================

	//共通グラフィック処理
	void Fighting::Grp ()
	{
		//----------------------------------------------------
		//@todo 共通のフラグポインタを MutalChara -> ExeChara まで渡す
	 
		//----------------------------------------------------
		//暗転
		UINT blackOut = m_mutualChara->GetBlackOut ();
		if ( 0 != blackOut )
		{
			m_bg->SetBlackOut ( blackOut );
			m_mutualChara->SetBlackOut ( 0 );
		}

		//----------------------------------------------------
		//白転
		UINT whiteOut = m_mutualChara->CheckWhiteOut () ? 60 : 0;
		if ( 0 != whiteOut )
		{
			m_bg->SetWhiteOut ( whiteOut );
			m_mutualChara->SetWhiteOut ( F );
		}

		//----------------------------------------------------
		//スロー


		if ( m_pFtgGrp->IsSlowStart () )
		{
			m_bg->SetBlackOut ( 60 );
		}

		if ( m_pFtgGrp->IsSlowLast () )
		{
			//スロウ解除
			m_bg->OffBlackOut ();
			m_mutualChara->RevertSlow ();
		}
		m_pFtgGrp->Move ();

		//----------------------------------------------------
		//背景通常処理
		m_bg->Grp ();
	}

#if 0
	//weak_ptrを設置
	void Fighting::AssignWp ( WP_FTG wp ) const
	{
		m_mutualChara->AssignWp ( wp );
	}
#endif // 0


#endif // 0
}	//namespace GAME

