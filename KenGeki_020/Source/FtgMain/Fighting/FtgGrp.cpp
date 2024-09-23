﻿//=================================================================================================
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
		m_tmrStop.Clear ();
		m_tmrBlackOut.Clear ();

		m_fade_white = std::make_shared < FadeRect > ();
		TASK_VEC::AddpTask ( m_fade_white );
		GRPLST_INSERT ( m_fade_white );
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
		m_tmrSlow.Init ();
		m_tmrStop.Init ();
		m_tmrBlackOut.Init ();

		TASK_VEC::Init ();
	}

	void FtgGrp::Move ()
	{
		m_tmrSlow.Move ();
		m_tmrStop.Move ();
		m_tmrBlackOut.Move ();

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

		TASK_VEC::Move ();
	}


}	//namespace GAME

