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
		m_tmrSlow.Clear ();
//		TASK_VEC::AddpTask ( m_tmrSlow );
		m_tmrStop.Clear ();
//		TASK_VEC::AddpTask ( m_tmrStop );

		m_fade_white = std::make_shared < FadeRect > ();
		TASK_VEC::AddpTask ( m_fade_white );
		GRPLST_INSERT ( m_fade_white );
	}

	FtgGrp::~FtgGrp ()
	{
	}

	void FtgGrp::Load ()
	{
		//test 動画
		mp_vtx = std::make_unique < s3d::VideoTexture > ( U"raiden.mp4", s3d::Loop::No );
		GrpLst::Inst()->SetupVtx ( std::move ( mp_vtx ) );

		TASK_VEC::Load ();
	}

	void FtgGrp::Init ()
	{
		m_tmrSlow.Init ();
		m_tmrStop.Init ();

		TASK_VEC::Init ();
	}

	void FtgGrp::Move ()
	{
		m_tmrSlow.Move ();
		m_tmrStop.Move ();

		//---------------------------------------------------
		//超必殺カットイン
		if ( m_overdrive )
		{
		m_fade_white->SetWhiteOut ( 60 );
			GrpLst::Inst()->StartVtx ();
			m_overdrive = F;	//条件をオフ
		}

		TASK_VEC::Move ();
	}

	void FtgGrp::StartSlow ()
	{
		m_tmrSlow.Start ( 60 );
	}

	void FtgGrp::StartStop ( UINT i )
	{
		m_tmrStop.Start ( i );
	}


}	//namespace GAME

