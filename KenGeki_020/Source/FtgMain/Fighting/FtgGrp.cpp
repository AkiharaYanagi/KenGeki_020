//=================================================================================================
//
//	FtgGrp ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "FtgGrp.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	FtgGrp::FtgGrp ()
	{
		m_fade_white = std::make_shared < FadeRect > ();
		TASK_VEC::AddpTask ( m_fade_white );
		GRPLST_INSERT ( m_fade_white );

		//------------------------------------------------
		//暗転
		m_bg_black = std::make_shared < PrmRect > ();
		m_bg_black->SetRect ( 0, 0, 1280, 960 );
		m_bg_black->SetColor ( s3d::Color ( 0, 0, 0, 128 ) );
		m_bg_black->SetZ ( Z_BG );
		AddpTask ( m_bg_black );
		GRPLST_INSERT ( m_bg_black );
		m_bg_black->SetValid ( F );

		//------------------------------------------------
		//白転
		m_bg_White = std::make_shared < PrmRect > ();
		m_bg_White->SetRect ( 0, 0, 1280, 960 );
		m_bg_White->SetColor ( s3d::Color ( 255, 255, 255, 255 ) );
		m_bg_White->SetZ ( Z_BG );
		AddpTask ( m_bg_White );
		GRPLST_INSERT ( m_bg_White );
		m_bg_White->SetValid ( F );
	}

	FtgGrp::~FtgGrp ()
	{
	}

	void FtgGrp::Load ()
	{
#if 0
		//test 動画
		mp_vtx = std::make_unique < s3d::VideoTexture > ( U"raiden.mp4", s3d::Loop::No );
		GrpLst::Inst()->SetupVtx ( std::move ( mp_vtx ) );
#endif // 0

		TASK_VEC::Load ();
	}

	void FtgGrp::Init ()
	{
		m_tmrScpStop.Init ();
		m_tmrBlackOut.Init ();
		m_tmrWhiteOut.Init ();
		m_tmrSlow.Init ();
		m_tmrVibration.Init ();

		TASK_VEC::Init ();
	}

	void FtgGrp::Move ()
	{
		//-------------------------------------------------------
		//暗転
		if ( m_tmrBlackOut.IsActive () )
		{
			//初回
			if ( m_tmrBlackOut.IsStart () )
			{
				m_bg_black->SetValid ( T );
			}
			//終回
			if ( m_tmrBlackOut.IsLast () )
			{
				m_bg_black->SetValid ( F );
			}
		}

		//-------------------------------------------------------
		//白転
		if ( m_tmrWhiteOut.IsActive () )
		{
			//初回
			if ( m_tmrWhiteOut.IsStart () )
			{
				m_bg_White->SetValid ( T );
			}
			//終回
			if ( m_tmrWhiteOut.IsLast () )
			{
				m_bg_White->SetValid ( F );
			}
		}

		//---------------------------------------------------
		//超必殺カットイン
		if ( m_overdrive )
		{
#if 0
			m_fade_white->SetWhiteOut ( 60 );
			GrpLst::Inst()->StartVtx ();
#endif // 0
			m_overdrive = F;	//条件をオフ
		}


		//---------------------------------------------------
		//振動
		if ( m_tmrVibration.IsActive () )
		{
			if ( m_tmrVibration.IsStart () )
			{
				G_GrpTx::Inst()->VibOn ();
			}
			if ( m_tmrVibration.IsLast () )
			{
				G_GrpTx::Inst()->VibOff ();
			}

		}



		//---------------------------------------------------
		//タイマ動作
		m_tmrScpStop.Move ();
		m_tmrBlackOut.Move ();
		m_tmrWhiteOut.Move ();
		m_tmrSlow.Move ();
		m_tmrVibration.Move ();

		TASK_VEC::Move ();
	}


}	//namespace GAME

