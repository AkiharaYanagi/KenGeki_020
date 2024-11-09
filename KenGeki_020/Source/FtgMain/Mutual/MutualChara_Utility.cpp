//=================================================================================================
//
//	両者キャラ　利用関数群
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "MutualChara_Utility.h"
#include "../../GameMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	MutualChara_Utility::MutualChara_Utility ()
	{
	}

	MutualChara_Utility::~MutualChara_Utility ()
	{
	}

	void MutualChara_Utility::ParamInit ( P_Param p )
	{
		MUTCH_MODE mode = p->GetMutchMode ();
		switch ( mode )
		{
		case MUTCH_MODE::MODE_PLAYER_CPU:
			cpu1 = F; cpu2 = T;
			break;
		case MUTCH_MODE::MODE_PLAYER_PLAYER:
			cpu1 = F; cpu2 = F;
			break;
		case MUTCH_MODE::MODE_CPU_CPU:
			cpu1 = T; cpu2 = T;
			break;
		}
	}

	void MutualChara_Utility::SetpChara ( P_ExeChara p1, P_ExeChara p2 )
	{
		m_exeChara1 = p1;
		m_exeChara2 = p2;

		//------------------------------------------------
		//デバッグ用枠表示初期切替
#define DISP_RECT	1
#if DISP_RECT
		OnDispRect ();
		OnDispInput ();
		OnDispFrontEnd ();
#else
		OffDispRect ();
		OffDispInput ();
		OffDispFrontEnd ();
#endif // DISP_RECT


		//CPU操作表示は初期値でON
		OnDispPlayerInput ();
//		OffDispPlayerInput ();
	}

	//------------------------------------------------------
	//枠表示切替 
	//@info ExeCharaで呼ぶと1P2Pで２回呼ばれてしまう
	void MutualChara_Utility::SwitchRect ()
	{
		is_bDispRect = ( WND_UTL::AscKey ( '2' ) );

		//@info キーボード入力は押しっぱなしで一定時間後連打状態になる
		//TRACE_F ( _T ( "b = %d, pre = %d, is = %d\n" ), bDispRect ? 1 : 0, pre_bDispRect ? 1 : 0, is_bDispRect ? 1 : 0  );

		//今回押した瞬間ならば、1回のみ切替
		if ( ! pre_bDispRect && is_bDispRect )	// false -> true
		{
			if ( ! bDispRect )
			{
				OnDispRect ();
			}
			else
			{
				OffDispRect ();
			}
		}
		pre_bDispRect = is_bDispRect;
	}

	void MutualChara_Utility::OnDispRect ()
	{
		m_exeChara1->OnDispRect ();
		m_exeChara2->OnDispRect ();
		bDispRect = T;
	}

	void MutualChara_Utility::OffDispRect ()
	{
		m_exeChara1->OffDispRect ();
		m_exeChara2->OffDispRect ();
		bDispRect = F;
	}


	//------------------------------------------------------
	//入力表示切替
	void MutualChara_Utility::SwitchDispInput ()
	{
		is_bDispInput = ( WND_UTL::AscKey ( '3' ) );

		//今回押した瞬間ならば、1回のみ切替
		if ( ! pre_bDispInput && is_bDispInput )	// false -> true
		{
			if ( ! bDispInput )
			{
				OnDispInput ();
			}
			else
			{
				OffDispInput ();
			}
		}

		pre_bDispInput = is_bDispInput;
	}

	void MutualChara_Utility::OnDispInput ()
	{
		m_exeChara1->OnDispInput ();
		m_exeChara2->OnDispInput ();
		bDispInput = T;
	}

	void MutualChara_Utility::OffDispInput ()
	{
		m_exeChara1->OffDispInput ();
		m_exeChara2->OffDispInput ();
		bDispInput = F;
	}

	//------------------------------------------------------
	//ゲージ類表示切替
	void MutualChara_Utility::SwitchFrontEnd ()
	{
		is_bFrontEnd = ( WND_UTL::AscKey ( '4' ) );
		//Asyncの最初の１回
		G_FTG()->SetSysDisp ( is_bFrontEnd );


		//今回押した瞬間ならば、1回のみ切替
		if ( ! pre_bFrontEnd && is_bFrontEnd )	// false -> true
		{
			if ( ! bFrontEnd )
			{
				OnDispFrontEnd ();
			}
			else
			{
				OffDispFrontEnd ();
			}
		}

		pre_bFrontEnd = is_bFrontEnd;
	}

	void MutualChara_Utility::OnDispFrontEnd ()
	{
		m_exeChara1->OnFrontEnd ();
		m_exeChara2->OnFrontEnd ();
		bFrontEnd = T;
	}

	void MutualChara_Utility::OffDispFrontEnd ()
	{
		m_exeChara1->OffFrontEnd ();
		m_exeChara2->OffFrontEnd ();
		bFrontEnd = F;
	}


	//------------------------------------------------------
	//プレイヤCPU表示切替
	void MutualChara_Utility::SwitchPlayerInput ()
	{
		is_bDispPlayerInput = ( WND_UTL::AscKey ( '5' ) );
		//Asyncの最初の１回
		//G_FTG()->SetSysDisp ( is_bDispPlayerInput );


		//今回押した瞬間ならば、1回のみ切替
		if ( ! pre_bDispPlayerInput && is_bDispPlayerInput )	// false -> true
		{
			if ( ! bDispPlayerInput )
			{
				OnDispPlayerInput ();
			}
			else
			{
				OffDispPlayerInput ();
			}
		}

		pre_bDispPlayerInput = is_bDispPlayerInput;
	}

	void MutualChara_Utility::OnDispPlayerInput ()
	{
		m_exeChara1->On_DispPlayerInput ();
		m_exeChara2->On_DispPlayerInput ();
		bDispPlayerInput = T;
	}

	void MutualChara_Utility::OffDispPlayerInput ()
	{
		m_exeChara1->Off_DispPlayerInput ();
		m_exeChara2->Off_DispPlayerInput ();
		bDispPlayerInput = F;
	}


	//------------------------------------------------------
	void MutualChara_Utility::SetCPU_1P ( bool bCPU )
	{
		cpu1 = bCPU;
	}
	
	void MutualChara_Utility::SetCPU_2P ( bool bCPU )
	{
		cpu2 = bCPU;
	}
	
	 
	//CPU操作切替
	void MutualChara_Utility::SwitchCPU ()
	{
		if ( WND_UTL::AscKey ( '6' ) )
		{
			cpu1 ^= T;
			if ( cpu1 )
			{
				m_exeChara1->ControlCPU ();
			}
			else
			{
				m_exeChara1->ControlPlayer ();
			}
		}

		if ( WND_UTL::AscKey ( '7' ) )
		{
			cpu2 ^= T;
			if ( cpu2 )
			{
				m_exeChara2->ControlCPU ();
			}
			else
			{
				m_exeChara2->ControlPlayer ();
			}
		}
	}


}	//namespace GAME

