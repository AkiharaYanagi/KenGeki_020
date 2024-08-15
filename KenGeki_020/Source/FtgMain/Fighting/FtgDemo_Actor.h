//=================================================================================================
//
//	Fighting デモ
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../FtgConst.h"	
#include "../Mutual/MutualChara.h"
#include "FtgDemo_State.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	using VP_FtgDemo = std::vector < P_FtgDemo >;

	//Actor
	class FtgDemoActor : public TASK_VEC, public std::enable_shared_from_this < FtgDemoActor >
	{
		//ステート
		P_FTG_DM_Greeting	m_Greeting;
		P_FTG_DM_GetReady	m_GetReady;
		P_FTG_DM_Attack		m_Attack;
		P_FTG_DM_Main		m_Main;
		P_FTG_DM_WallBreak	m_WallBreak;
		P_FTG_DM_Down		m_Down;	
		P_FTG_DM_TimeUp		m_TimeUp;		//タイムアップ
		P_FTG_DM_TimeUpWait	m_TimeUpWait;		//タイムアップ	待機
		P_FTG_DM_Winner		m_Winner;


		//ステート監理
		VP_FtgDemo			mvp_FtgDemo;

		//現在ステート
		P_FtgDemo			mp_FtgDemo;

		//デモ共通パラメータ
		P_PRM_FTG_DEMO		mp_Param;

		//終了フラグ
		bool				m_bEnd;

	public:
		FtgDemoActor ();

		void StartGreeting ();
		void StartFighting ();

		void ParamLoad ( P_Param p );
		void Load ();
		void Do ();

		void SetwpFighting ( WP_Fighting wp ) { mp_Param->SetwpFighting ( wp ); }
		void SetpMutualChara ( P_MutualChara p ) { mp_Param->SetpMutualChara ( p ); }
		void SetpFtgGrp ( P_FtgGrp p ) { mp_Param->SetpFtgGrp ( p ); }

		void Change_Greeting_To_GetReady ();
		void Change_GetReady_To_Attack ();
		void Change_Main_To_Down ();
		void Change_Main_To_TimeUpWait ();
		void Change_Main_To_TimeUp ();
		void Change_TimeUp_To_Winner ();
		void Change_Down_To_Greeting ();


		//Start()を用いない一時変更
		void Shift_Main_To_WallBreak ();
		void Shift_WallBreak_To_Main ();

		
		void End_Down_To_Result ();
		bool IsEnd () const { return m_bEnd; }

		s3d::String GetName () const { return mp_FtgDemo->GetName (); }

	private:
		P_MutualChara GetpMutualChara () const { return mp_Param->GetpMutualChara (); }
	};

	using P_FtgDemoActor = std::shared_ptr < FtgDemoActor >;


}	//namespace GAME


