//=================================================================================================
//
// DispChara ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../../GameMain/Param.h"
#include "DispMainImage.h"
#include "DispInput.h"
#include "DispRect.h"
#include "../Main/ExCh_State.h"

#if 0
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/G_Ftg.h"
#include "../Input/CharaInput.h"
#endif // 0



#if 0
#include "DispFrontEnd.h"
#endif // 0
#include "DispFrontEnd_all.h"





//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class DispChara : public TASK_VEC
	{
		P_DispMainImage	m_mainImage;	//メインイメージ
		P_DispInput		m_dispInput;	//入力表示
		P_DispRect		m_dispRect;		//枠



		//移行中
		//P_DispFrontEnd	m_frontEnd;		//フロントエンド
		P_DispFrontEnd_all	m_frontEnd_all;		//フロントエンド
		


	public:
		DispChara ();
		DispChara ( const DispChara & rhs ) = delete;
		~DispChara ();

		void Move ();

		void ParamInit ( P_Param pParam );

		//プレイヤ側によりゲージ類の表示部のみ初期化
		void LoadPlayer ( PLAYER_ID playerID );

		//キャラを設定する
		void SetpChara ( const P_Chara pChara );

		//表示枠設定
		void SetpCharaRect ( P_CharaRect pCharaRect );

		//更新
		void Update ( P_Action pAct, P_Script pScp, const BtlParam & btlprm, P_CharaInput pChIpt );

		void UpdateStateName ( s3d::String stateName );

		//終了時
		void EndBattle ();
		
		//------------------------------------------------
		//@info 表示切替
		//  ExeChara以下で行うと1P2Pで2回呼ばれるのでMutualCharaなどで呼び出す

		void OnInput () { m_dispInput->On (); }
		void OffInput () { m_dispInput->Off (); }
		
		void OnRect () { m_dispRect->OnRect (); }		//枠表示ON
		void OffRect () { m_dispRect->OffRect (); }		//枠表示OFF



		void OnFrontEnd ()
		{
#if 0
			m_frontEnd->On ();
#endif // 0
		}
		void OffFrontEnd ()
		{
#if 0
			m_frontEnd->Off ();
#endif // 0
		}

		void On_DispPlayerInput ()
		{
#if 0
			m_frontEnd->On_DispPlayerInput ();
#endif // 0
		}
		void Off_DispPlayerInput ()
		{
#if 0
			m_frontEnd->Off_DispPlayerInput ();
#endif // 0
		}

		//------------------------------------------------

		//PLAYER / CPU
		void SetControl_PLAYER ()
		{
#if 0
			m_frontEnd->SetPlayer ();
#endif // 0
		}
		void SetControl_CPU ()
		{
#if 0
			m_frontEnd->SetCPU ();
#endif // 0
		}



#if 0

		//色変更
		void SetColor ( _CLR clr ) { m_mainImage->SetColor ( clr ); }

		//影化
		void TurnShadow ( bool b ) { m_mainImage->TurnShadow ( b ); }
#endif // 0

		//影化
		void TurnShadow ( bool b ) { m_mainImage->TurnShadow ( b ); }

		//乗算カラー指定
		void SetColor ( uint32 clr ) { m_mainImage->SetColor ( clr ); }

		//メインイメージを同一Z値で先頭にする
		void TopByZ () { m_mainImage->TopByZ (); }


	private:
		//メインイメージの更新
		void UpdateMainImage ( P_Script pScript, const BtlParam & btlprm );

		//入力更新
		void UpdateInput ( P_CharaInput p );

		//ゲージ類更新
		void UpdateGauge ( const BtlParam & btlPrm );

		//ヒット数更新
		void UpdateChainHitNum ( const BtlParam & btlPrm );
	};


	using P_DispChara = std::shared_ptr < DispChara >;


}	//namespace GAME


