#include "../../GameMain/Param.h"
//=================================================================================================
//
//	両者キャラ　利用関数群
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../ExeChara/Main/ExeChara.h"
#include "../../GameMain/Param.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	class MutualChara_Utility
	{
		//キャラ
		P_ExeChara		m_exeChara1;
		P_ExeChara		m_exeChara2;

		bool bDispRect { T };		//状態
		bool pre_bDispRect { F };	//前回押しているか
		bool is_bDispRect { F };	//今回押しているか

		bool bDispInput { T };		//状態
		bool pre_bDispInput { F };	//前回押しているか
		bool is_bDispInput { F };	//今回押しているか

		bool bFrontEnd { T };		//状態
		bool pre_bFrontEnd { F };	//前回押しているか
		bool is_bFrontEnd { F };	//今回押しているか

		bool bDispPlayerInput { T };		//状態
		bool pre_bDispPlayerInput { F };	//前回押しているか
		bool is_bDispPlayerInput { F };		//今回押しているか

		bool cpu1 { F };	//CPU状態
		bool cpu2 { F };	//CPU状態

	public:
		MutualChara_Utility ();
		MutualChara_Utility ( const MutualChara_Utility & rhs ) = delete;
		~MutualChara_Utility ();

		void ParamInit ( P_Param p );
		void SetpChara ( P_ExeChara p1, P_ExeChara p2 );

		void SwitchRect ();			//枠表示切替
		void OnDispRect ();
		void OffDispRect ();

		void SwitchDispInput ();	//入力表示切替
		void OnDispInput ();
		void OffDispInput ();

		void SwitchFrontEnd ();		//ゲージ類表示切替
		void OnDispFrontEnd ();
		void OffDispFrontEnd ();

		void SwitchPlayerInput ();		//プレイヤインプット表示切替
		void OnDispPlayerInput ();
		void OffDispPlayerInput ();

		void SetCPU_1P ( bool bCPU );	//T:CPU, F:PLAYER
		void SetCPU_2P ( bool bCPU );	//T:CPU, F:PLAYER
		void SwitchCPU ();			//2PをCPU操作切替
	};


}	//namespace GAME

