﻿//=================================================================================================
//
//	Round ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Round.h"
#include "../FtgConst.h"	
#include "../../GameMain/G_Ftg.h"	


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	const uint32 Round::TX_0 = 0;
	const uint32 Round::TX_1 = 1;

	const float Round::POS_BY = 105;
	const float Round::POS_BX10 = 640 - 100;
	const float Round::POS_BX11 = 640 - 100 - 40;
	const float Round::POS_BX20 = 640 + 100 - 64;
	const float Round::POS_BX21 = 640 + 100 - 64 + 40;

	Round::Round ()
	{
		m_roundDisp_1p = std::make_shared < GameGraphic > ();
		m_roundDisp_1p->AddTexture_FromArchive ( U"WinMark_Frame.png" );
		m_roundDisp_1p->AddTexture_FromArchive ( U"WinMark_Win.png" );
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

		m_roundDisp_2p = std::make_shared < GameGraphic > ();
		m_roundDisp_2p->AddTexture_FromArchive ( U"WinMark_Frame.png" );
		m_roundDisp_2p->AddTexture_FromArchive ( U"WinMark_Win.png" );
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
		//m_round_1p = 0;
		//m_round_2p = 0;
		TASK_VEC::Init ();
	}


	void Round::Move ()
	{
		//ラウンド現在数で表示を切替
		switch ( m_round_1p )
		{
		case 0:
			m_ob_1p0->SetIndexTexture ( TX_0 );
			m_ob_1p1->SetIndexTexture ( TX_0 );
			break;
		case 1:
			m_ob_1p0->SetIndexTexture ( TX_1 );
			m_ob_1p1->SetIndexTexture ( TX_0 );
			break;
		case 2:
			m_ob_1p0->SetIndexTexture ( TX_1 );
			m_ob_1p1->SetIndexTexture ( TX_1 );
			break;
		}

		switch ( m_round_2p )
		{
		case 0:
			m_ob_2p0->SetIndexTexture ( TX_0 );
			m_ob_2p1->SetIndexTexture ( TX_0 );
			break;
		case 1:
			m_ob_2p0->SetIndexTexture ( TX_1 );
			m_ob_2p1->SetIndexTexture ( TX_0 );
			break;
		case 2:
			m_ob_2p0->SetIndexTexture ( TX_1 );
			m_ob_2p1->SetIndexTexture ( TX_1 );
			break;
		}


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


	void Round::On ()
	{
		m_roundDisp_1p->SetValid ( T );
		m_roundDisp_2p->SetValid ( T );
		m_ob_1p0->SetValid ( T );
		m_ob_1p1->SetValid ( T );
		m_ob_2p0->SetValid ( T );
		m_ob_2p1->SetValid ( T );
	}

	void Round::Off ()
	{
		m_roundDisp_1p->SetValid ( F );
		m_roundDisp_2p->SetValid ( F );
		m_ob_1p0->SetValid ( F );
		m_ob_1p1->SetValid ( F );
		m_ob_2p0->SetValid ( F );
		m_ob_2p1->SetValid ( F );
	}


}	//namespace GAME

