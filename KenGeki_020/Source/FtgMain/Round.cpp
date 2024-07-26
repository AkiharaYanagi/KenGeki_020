//=================================================================================================
//
//	Round ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Round.h"
#include "FtgConst.h"	
#include "G_Ftg.h"	


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const float Round::POS_BY = 105;
	const float Round::POS_BX10 = 640 - 100;
	const float Round::POS_BX11 = 640 - 100 - 40;
	const float Round::POS_BX20 = 640 + 100 - 64;
	const float Round::POS_BX21 = 640 + 100 - 64 + 40;

	Round::Round ()
	{
//		m_roundDisp_1p = std::make_shared < GameGraphic > ( U"WinMark_Frame.png" );
		m_roundDisp_1p->AddTexture ( U"WinMark_Win.png" );
		m_roundDisp_1p->SetZ ( Z_SHADOW );
		AddpTask ( m_roundDisp_1p );
		GRPLST_INSERT ( m_roundDisp_1p );

		m_ob_1p0 = std::make_shared < GameObject > ();
		m_ob_1p0->SetPos ( VEC2 ( POS_BX10, POS_BY ) );
		m_ob_1p1 = std::make_shared < GameObject > ();
		m_ob_1p1->SetPos ( VEC2 ( POS_BX11, POS_BY ) );
		m_roundDisp_1p->ClearObject ();
		m_roundDisp_1p->AddpObject ( m_ob_1p0 );
		m_roundDisp_1p->AddpObject ( m_ob_1p1 );

//		m_roundDisp_2p = std::make_shared < GameGraphic > ( U"WinMark_Frame.png" );
		m_roundDisp_2p->AddTexture ( U"WinMark_Win.png" );
		m_roundDisp_2p->SetZ ( Z_SHADOW );
		AddpTask ( m_roundDisp_2p );
		GRPLST_INSERT ( m_roundDisp_2p );

		m_ob_2p0 = std::make_shared < GameObject > ();
		m_ob_2p0->SetPos ( VEC2 ( POS_BX20, POS_BY ) );
		m_ob_2p1 = std::make_shared < GameObject > ();
		m_ob_2p1->SetPos ( VEC2 ( POS_BX21, POS_BY ) );
		m_roundDisp_2p->ClearObject ();
		m_roundDisp_2p->AddpObject ( m_ob_2p0 );
		m_roundDisp_2p->AddpObject ( m_ob_2p1 );
	}

	Round::~Round ()
	{
	}


	void Round::Init ()
	{
		TASK_VEC::Init ();
	}


	void Round::Move ()
	{
		TASK_VEC::Move ();
	}

	void Round::SetRound_1p ( UINT i )
	{
		m_round_1p = i;
		if ( i == 1 ) { m_ob_1p0->SetIndexTexture ( 1 ); }
		if ( i == 2 ) { m_ob_1p1->SetIndexTexture ( 1 ); }
	}

	void Round::AddRound_1p ()
	{
		++ m_round_1p;
		if ( m_round_1p == 1 ) { m_ob_1p0->SetIndexTexture ( 1 ); }
		if ( m_round_1p == 2 ) { m_ob_1p1->SetIndexTexture ( 1 ); }
	}

	void Round::SetRound_2p ( UINT i )
	{
		m_round_2p = i;
		if ( i == 1 ) { m_ob_2p0->SetIndexTexture ( 1 ); }
		if ( i == 2 ) { m_ob_2p1->SetIndexTexture ( 1 ); }
	}

	void Round::AddRound_2p ()
	{
		++ m_round_2p;
		if ( m_round_2p == 1 ) { m_ob_2p0->SetIndexTexture ( 1 ); }
		if ( m_round_2p == 2 ) { m_ob_2p1->SetIndexTexture ( 1 ); }
	}

	bool Round::IsEndMutch ()
	{
		return ( m_round_1p == m_targetRound || m_round_2p == m_targetRound );
	}


}	//namespace GAME

