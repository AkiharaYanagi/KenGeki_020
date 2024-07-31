//=================================================================================================
//
//	両者キャラ　利用関数群
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "MutualChara_Utility.h"

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

	void MutualChara_Utility::SetpChara ( P_ExeChara p1, P_ExeChara p2 )
	{
		m_exeChara1 = p1;
		m_exeChara2 = p2;

		//------------------------------------------------
		//デバッグ用枠表示初期切替
#define DISP_RECT	1
#if DISP_RECT
//		bDispRect = T;
		m_exeChara1->OnDispRect ();
		m_exeChara2->OnDispRect ();
#else
		m_exeChara1->OffDispRect ();
		m_exeChara2->OffDispRect ();
#endif // DISP_RECT
	}

	//------------------------------------------------------
	//入力表示切替
	void MutualChara_Utility::SwitchDispInput ()
	{
		static bool bDispInput = T;		//状態
		static bool pre_bDispInput = F;	//前回押しているか
		static bool is_bDispInput = F;	//今回押しているか

		is_bDispInput = ( WND_UTL::AscKey ( '2' ) );

		//今回押した瞬間ならば、1回のみ切替
		if ( ! pre_bDispInput && is_bDispInput )	// false -> true
		{
			if ( ! bDispInput )
			{
				m_exeChara1->OnDispInput ();
				m_exeChara2->OnDispInput ();
				bDispInput = true;
			}
			else
			{
				m_exeChara1->OffDispInput ();
				m_exeChara2->OffDispInput ();
				bDispInput = false;
			}
		}

		pre_bDispInput = is_bDispInput;
	}

	//------------------------------------------------------
	//枠表示切替 
	//@info ExeCharaで呼ぶと1P2Pで２回呼ばれてしまう
	void MutualChara_Utility::SwitchRect ()
	{
		static bool bDispRect = T;		//状態
		static bool pre_bDispRect = F;	//前回押しているか
		static bool is_bDispRect = F;	//今回押しているか

		is_bDispRect = ( WND_UTL::AscKey ( '1' ) );

		//@info キーボード入力は押しっぱなしで一定時間後連打状態になる
		//TRACE_F ( _T ( "b = %d, pre = %d, is = %d\n" ), bDispRect ? 1 : 0, pre_bDispRect ? 1 : 0, is_bDispRect ? 1 : 0  );

		//今回押した瞬間ならば、1回のみ切替
		if ( ! pre_bDispRect && is_bDispRect )	// false -> true
		{
			if ( ! bDispRect )
			{
				m_exeChara1->OnDispRect ();
				m_exeChara2->OnDispRect ();
				bDispRect = T;
			}
			else
			{
				m_exeChara1->OffDispRect ();
				m_exeChara2->OffDispRect ();
				bDispRect = F;
			}
		}
		pre_bDispRect = is_bDispRect;
	}

	//------------------------------------------------------
	//ゲージ類表示切替
	void MutualChara_Utility::SwitchFrontEnd ()
	{
		static bool bFrontEnd = T;		//状態
		static bool pre_bFrontEnd = F;	//前回押しているか
		static bool is_bFrontEnd = F;	//今回押しているか

		is_bFrontEnd = ( WND_UTL::AscKey ( '3' ) );

		//今回押した瞬間ならば、1回のみ切替
		if ( ! pre_bFrontEnd && is_bFrontEnd )	// false -> true
		{
			if ( ! bFrontEnd )
			{
				m_exeChara1->OnFrontEnd ();
				m_exeChara2->OnFrontEnd ();
				bFrontEnd = true;
			}
			else
			{
				m_exeChara1->OffFrontEnd ();
				m_exeChara2->OffFrontEnd ();
				bFrontEnd = false;
			}
		}

		pre_bFrontEnd = is_bFrontEnd;
	}

#if 0

	//------------------------------------------------------
	//CPU操作切替
	void MutualChara_Utility::SwithcCPU ()
	{
		static bool cpu1 = F;
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

		static bool cpu2 = F;
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

#endif // 


}	//namespace GAME

