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

	public:
		MutualChara_Utility ();
		MutualChara_Utility ( const MutualChara_Utility & rhs ) = delete;
		~MutualChara_Utility ();

		void SetpChara ( P_ExeChara p1, P_ExeChara p2 );

		void SwitchRect ();			//枠表示切替
		void SwitchDispInput ();	//入力表示切替
		void SwitchFrontEnd ();		//ゲージ類表示切替
		void SwitchCPU ();			//2PをCPU操作切替
	};


}	//namespace GAME

