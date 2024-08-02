//=================================================================================================
//
//	Fighting デモ
//
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "FtgDemo_Actor.h"
//#include <iomanip>	//std::setw(), std::setfill() など
#include "../GameMain/SoundConst.h"


//-------------------------------------------------------------------------------------------------
// 定義
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	FtgDemoActor::FtgDemoActor ()
		: m_bEnd ( F )
	{
		//ステート
		m_Greeting = std::make_shared < FTG_DM_Greeting > ();
		m_GetReady = std::make_shared < FTG_DM_GetReady > ();
		m_Attack = std::make_shared < FTG_DM_Attack > ();
		m_Main = std::make_shared < FTG_DM_Main > ();
		m_WallBreak = std::make_shared < FTG_DM_WallBreak > ();
		m_Down = std::make_shared < FTG_DM_Down > ();
		m_TimeUp = std::make_shared < FTG_DM_TimeUp > ();
		m_TimeUpWait = std::make_shared < FTG_DM_TimeUpWait > ();
		m_Winner = std::make_shared < FTG_DM_Winner > ();

		mvp_FtgDemo.push_back ( m_Greeting );
		mvp_FtgDemo.push_back ( m_GetReady );
		mvp_FtgDemo.push_back ( m_Attack );
		mvp_FtgDemo.push_back ( m_Main );
		mvp_FtgDemo.push_back ( m_WallBreak );
		mvp_FtgDemo.push_back ( m_Down );
		mvp_FtgDemo.push_back ( m_TimeUp );
		mvp_FtgDemo.push_back ( m_TimeUpWait );
		mvp_FtgDemo.push_back ( m_Winner );

		for ( P_FtgDemo p : mvp_FtgDemo )
		{
			AddpTask ( p );
		}

		//初期ステート
		mp_FtgDemo = m_Greeting;

		//デモ共通パラメータ
		mp_Param = std::make_shared < FtgDemoParam > ();
		for ( P_FtgDemo p : mvp_FtgDemo )
		{
			p->SetpPrm ( mp_Param );
		}
	}

	void FtgDemoActor::ParamLoad ( P_Param p )
	{
		mp_Param->SetpSceneParam ( p );
	}

	void FtgDemoActor::Load ()
	{
		mp_Param->SetwpFtgDemoActor ( shared_from_this () );
		TASK_VEC::Load ();
	}

	void FtgDemoActor::StartGreeting ()
	{
		mp_FtgDemo = m_Greeting;
		GetpMutualChara ()->StartGreeting ();
		m_Greeting->Start ();
	}

	void FtgDemoActor::StartFighting ()
	{
		mp_FtgDemo = m_Main;
		m_Main->Start ();
	}

	void FtgDemoActor::Do ()
	{
		mp_FtgDemo->Do ();
	}

	void FtgDemoActor::Change_Greeting_To_GetReady ()
	{
		m_GetReady->Start ();
		mp_FtgDemo = m_GetReady;

		//BGM
		//SOUND->If_Play_Loop_BGM ( BGM_Main );
	}

	void FtgDemoActor::Change_GetReady_To_Attack ()
	{
		m_GetReady->Final ();
		m_Attack->Start ();

		mp_FtgDemo = m_Main;
		m_Main->Start ();
	}

	void FtgDemoActor::Change_Main_To_Down ()
	{
		m_Down->Start ();
		mp_FtgDemo = m_Down;
	}

	void FtgDemoActor::Change_Main_To_TimeUpWait ()
	{
		m_TimeUpWait->Start ();
		mp_FtgDemo = m_TimeUpWait;
	}

	void FtgDemoActor::Change_Main_To_TimeUp ()
	{
		m_TimeUp->Start ();
		mp_FtgDemo = m_TimeUp;
	}

	void FtgDemoActor::Change_TimeUp_To_Winner ()
	{
		m_Winner->Start ();
		mp_FtgDemo = m_Winner;
	}

	void FtgDemoActor::Change_Down_To_Greeting ()
	{
		GetpMutualChara ()->StartGreeting ();
		m_Greeting->Start ();
		mp_FtgDemo = m_Greeting;
	}

	void FtgDemoActor::Shift_Main_To_WallBreak ()
	{
		mp_FtgDemo = m_WallBreak;
		m_WallBreak->Start ();		//タイマのため毎回スタートをかける
	}

	void FtgDemoActor::Shift_WallBreak_To_Main ()
	{
		mp_FtgDemo = m_Main;
	}

	void FtgDemoActor::End_Down_To_Result ()
	{
		m_bEnd = T;
	}

}	//namespace GAME

