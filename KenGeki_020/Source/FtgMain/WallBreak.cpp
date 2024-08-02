//=================================================================================================
//
//	WallBreak ソースファイル
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "WallBreak.h"
#include "FtgConst.h"	
#include "G_Ftg.h"	


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	WallBreak::WallBreak ()
	{
		m_grp = std::make_shared < GameGraphic > ();
		m_grp->AddTexture_FromArchive ( U"break0.png" );
		m_grp->AddTexture_FromArchive ( U"break1.png" );
		m_grp->AddTexture_FromArchive ( U"break2.png" );
		m_grp->AddTexture_FromArchive ( U"break3.png" );
		m_grp->SetZ ( Z_SHADOW );
		AddpTask ( m_grp );
		GRPLST_INSERT ( m_grp );

		Off ();
	}

	WallBreak::~WallBreak ()
	{
	}


	void WallBreak::Init ()
	{
		m_index = 0;
		m_timer.Clear ();
		m_grp->SetValid ( F );

		TASK_VEC::Init ();
	}


	void WallBreak::Move ()
	{
		if ( m_timer.IsLast () )
		{
			if ( ++ m_index >= 4 )
			{
				Off ();
				return;
			}
			m_grp->SetIndexTexture ( m_index );
			m_timer.Start ();
		}

		m_timer.Move ();

		TASK_VEC::Move ();
	}

	void WallBreak::On ()
	{
		m_index = 0;
		m_grp->SetValid ( T );
		m_timer.Start ();
	}


	void WallBreak::Off ()
	{
		m_index = 0;
		m_timer.Clear ();
		m_grp->SetValid ( F );
	}

	void WallBreak::SetPos ( float x )
	{
		m_grp->SetPos ( VEC2 ( x, 0 ) );
	}



}	//namespace GAME

