//=================================================================================================
//
//	BG ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "BG.h"
#include "FtgConst.h"	
#include "G_Ftg.h"	


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const float BG::BG_SIZE_W = 2048;
	const float BG::BG_SIZE_H = 1024;
	const float BG::BG_POS_X = 0 - ( 2048 - 1280 ) / 2;
	const float BG::BG_POS_Y = 0 - ( 1024 - 960 );

	BG::BG ()
	{
		//------------------------------------------------
		//背景
//		m_bg = make_shared < GrpAcv > ();
		m_bg = std::make_shared < GrpBs > ();

		m_bg->AddTexture ( U"BG0.png" );

		m_bg->SetPos ( (float)BG_POS_X, (float)BG_POS_Y );
		m_bg->SetZ ( Z_BG );


#if 0
		//オブジェクト追加
		m_bg->AddObject ();
		P_Object pOb = m_bg->GetpvpObject ()->at ( 1 );
		pOb->SetPos ( 200, BG_POS_Y );
#endif // 0

		AddpTask ( m_bg );
//		GRPLST_INSERT_MAIN ( m_bg );

#if 0

//テスト
		m_bg_back = make_shared < GrpAcv > ();
		m_bg_back->AddTexture ( _T ( "BG0_Back.png" ) );
		m_bg_back->SetPos ( (float)BG_POS_X, (float)BG_POS_Y );
		m_bg_back->SetZ ( Z_BG );

		m_bg_middle = make_shared < GrpAcv > ();
		m_bg_middle->AddTexture ( _T ( "BG0_Middle.png" ) );
		m_bg_middle->SetPos ( (float)BG_POS_X, (float)BG_POS_Y );
		m_bg_middle->SetZ ( Z_BG );

		m_bg_front = make_shared < GrpAcv > ();
		m_bg_front->AddTexture ( _T ( "BG0_Front.png" ) );
		m_bg_front->SetPos ( (float)BG_POS_X, (float)BG_POS_Y );
		m_bg_front->SetZ ( Z_BG );

		AddpTask ( m_bg_back );
		GRPLST_INSERT_MAIN ( m_bg_back );
		AddpTask ( m_bg_middle );
		GRPLST_INSERT_MAIN ( m_bg_middle );
		AddpTask ( m_bg_front );
		GRPLST_INSERT_MAIN ( m_bg_front );
#endif // 0

#if 0
		//------------------------------------------------
		//暗転
		m_bg_black = make_shared < PrmRect > ();
		m_bg_black->SetSize ( 1280, 960 );
		m_bg_black->SetAllColor ( 0x80000000 );
		m_bg_black->SetPos ( 0, 0 );
		m_bg_black->SetZ ( Z_BG );
		AddpTask ( m_bg_black );
		GRPLST_INSERT_MAIN ( m_bg_black );
		m_bg_black->SetValid ( F );

		//------------------------------------------------
		//白背景
		m_bg_white = make_shared < PrmRect > ();
		m_bg_white->SetSize ( 1280, 960 );
		m_bg_white->SetAllColor ( 0xffffffff );
		m_bg_white->SetPos ( 0, 0 );
		m_bg_white->SetZ ( Z_BG );
		AddpTask ( m_bg_white );
		GRPLST_INSERT_MAIN ( m_bg_white );
		m_bg_white->SetValid ( F );

		//------------------------------------------------
		//test
		m_wall_L = make_shared < GrpAcv > ();
		m_wall_L->AddTexture ( _T ( "test_kabe.png" ) );
		m_wall_L->SetPos ( 0, 0 );
		m_wall_L->SetZ ( Z_BG );
		AddpTask ( m_wall_L );
		GRPLST_INSERT_MAIN ( m_wall_L );

		m_wall_R = make_shared < GrpAcv > ();
		m_wall_R->AddTexture ( _T ( "test_kabe.png" ) );
		m_wall_R->SetScaling ( -1.f, 1.f );
		m_wall_R->SetPos ( GAME_WIDTH - 512, 0 );
		m_wall_R->SetZ ( Z_BG );
		AddpTask ( m_wall_R );
		GRPLST_INSERT_MAIN ( m_wall_R );
		

		m_wall_L->SetValid ( F );
		m_wall_R->SetValid ( F );


		//------------------------------------------------
		//BGタイマ
		//暗転
		m_tmrBlackOut = make_shared < Timer > ();
		AddpTask ( m_tmrBlackOut );
		//白転
		m_tmrWhiteOut = make_shared < Timer > ();
		AddpTask ( m_tmrWhiteOut );

		//------------------------------------------------

		//壁割り
		m_wall_break = make_shared < GrpAcv > ();
		m_wall_break->AddTexture ( _T("glass.png") );
		m_wall_break->AddTexture ( _T("break0.png") );
		m_wall_break->AddTexture ( _T("break1.png") );
		m_wall_break->AddTexture ( _T("break2.png") );
		m_wall_break->AddTexture ( _T("break3.png") );
		m_wall_break->SetScaling ( 0.5f, 1.f );
		AddpTask ( m_wall_break );
		GRPLST_INSERT_MAIN ( m_wall_break );
		m_wall_break->SetValid ( F );

		m_tmrWallBreak = make_shared < Timer > ();
		AddpTask ( m_tmrWallBreak );
#endif // 0
	}

	BG::~BG ()
	{
	}


	void BG::Init ()
	{
#if 0
		m_bg_black->SetValid ( F );
		m_bg_white->SetValid ( F );

		m_tmrBlackOut->Clear ();
		m_tmrWhiteOut->Clear ();
		m_tmrWallBreak->Clear ();

#endif // 0
		TASK_LST::Init ();
	}


	void BG::Move ()
	{
#if 0
		//--------------------------
		//暗転
		if ( m_tmrBlackOut->IsActive () )	//稼働時
		{
			//終了
			if ( m_tmrBlackOut->IsLast () )
			{
				m_tmrBlackOut->Clear ();
				m_bg_black->SetValid ( F );
			}
		}

		//白転
		if ( m_tmrWhiteOut->IsActive () )	//稼働時
		{
			//終了
			if ( m_tmrWhiteOut->IsLast () )
			{
				m_tmrWhiteOut->Clear ();

				m_bg_white->SetValid ( F );
			}
		}

		//壁割り
		if ( m_tmrWallBreak->IsActive () )
		{
			//終了
			if ( m_tmrWallBreak->IsLast () )
			{
				m_wall_break->SetIndexTexture ( m_indexTexture );
				if ( ++ m_indexTexture > 3 )
				{
					m_indexTexture = 0; 
					m_wall_break->SetValid ( F );
				} 
				m_tmrWallBreak->Start ( 6 );
			}
		}

		//--------------------------
		//共通グラフィック処理
		Grp ();

#endif // 0
		//--------------------------
		TASK_LST::Move ();
	}

	//=============================================================
	//	内部関数
	//=============================================================

#if 0


	//共通グラフィック処理
	void BG::Grp ()
	{
#if 0
		//-------------------------------------------------------
		//暗転
		if ( ! m_tmrBlackOut->IsActive () )
		{
			UINT blackOut = m_mutualChara->GetBlackOut ();

			//初回
			if ( 0 < blackOut )
			{
				m_tmrBlackOut->Start ( blackOut );

				blackOut = 0;
				m_mutualChara->SetBlackOut ( 0 );

				m_bg->SetValid ( F );
				m_bg_blackout->SetValid ( T );
			}
		}

		//-------------------------------------------------------
		//白転
		if ( ! m_tmrWhiteOut->IsActive () )
		{
			//初回
			if ( m_mutualChara->CheckWhiteOut () )
			{
				m_tmrWhiteOut->Start ( 30 );

				m_bg_white->SetValid ( T );
				m_mutualChara->SetWhiteOut ( F );
			}
		}

#endif // 0
		//-------------------------------------------------------
		//背景位置補正
		int nx = (int) G_BASE_POS ().x;
		int disp_bg_x = nx % GAME_WIDTH;
		m_bg->SetPos ( (float)disp_bg_x, (float)BG_POS_Y );

		//サブ背景位置
		int lx = disp_bg_x - GAME_WIDTH;
		int rx = disp_bg_x + GAME_WIDTH;
		const int D = GAME_WINDOW_WIDTH - GAME_WIDTH;	//2048 - 1280 = 768
		int sub_x = ( - disp_bg_x < 0 )? lx : rx ;
		P_Object pOb = m_bg->GetpObject ( 1 );
		pOb->SetPos ( (float)sub_x, (float)BG_POS_Y );


		//カベ位置
		float wall_l = G_FTG->GetWallLeft ();
		m_wall_L->SetPos ( wall_l + G_BASE_POS ().x, 0 );

		float wall_r = G_FTG->GetWallRight ();
		m_wall_R->SetPos ( wall_r + G_BASE_POS ().x, 0 );
	}


	void BG::SetBlackOut ( UINT n )
	{
		m_tmrBlackOut->Start ( n );
//		m_bg->SetValid ( F );
//		m_bg_blackout->SetValid ( T );
		m_bg_black->SetValid ( T );
	}

	void BG::OffBlackOut ()
	{
		m_tmrBlackOut->Clear ();
		m_bg_black->SetValid ( F );
	}

	void BG::SetWhiteOut ( UINT n )
	{
		m_tmrWhiteOut->Start ( n );
		m_bg_white->SetValid ( T );
	}

	void BG::StartWallBreak_L ()
	{
		m_tmrWallBreak->Start ( 4 );
		m_wall_break->SetPos ( 0, 0 );
		m_wall_break->SetValid ( T );
	}
	void BG::StartWallBreak_R ()
	{
		m_tmrWallBreak->Start ( 4 );
		m_wall_break->SetValid ( T );
		m_wall_break->SetPos ( GAME_WINDOW_WIDTH / 2, 0 );
	}


#endif // 0

}	//namespace GAME

