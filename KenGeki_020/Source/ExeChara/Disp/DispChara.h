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
#include "DispFrontEnd.h"
#include "../Main/ExCh_State.h"

#if 0
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/G_Ftg.h"
#include "../Input/CharaInput.h"
#endif // 0


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
		P_DispFrontEnd	m_frontEnd;		//フロントエンド

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

		//------------------------------------------------
		//@info 表示切替
		//  ExeChara以下で行うと1P2Pで2回呼ばれるのでMutualCharaなどで呼び出す

		void OnInput () { m_dispInput->On (); }
		void OffInput () { m_dispInput->Off (); }
		
		void OnRect () { m_dispRect->OnRect (); }		//枠表示ON
		void OffRect () { m_dispRect->OffRect (); }		//枠表示OFF

		void OnFrontEnd () { m_frontEnd->On (); }
		void OffFrontEnd () { m_frontEnd->Off (); }
#if 0

		//------------------------------------------------

		//PLAYER / CPU
		void SetControl_PLAYER () { m_frontEnd->SetPlayer (); }
		void SetControl_CPU () { m_frontEnd->SetCPU (); }


		//色変更
		void SetColor ( _CLR clr ) { m_mainImage->SetColor ( clr ); }

		//影化
		void TurnShadow ( bool b ) { m_mainImage->TurnShadow ( b ); }
#endif // 0


	private:
		//メインイメージの更新
		void UpdateMainImage ( P_Script pScript, const BtlParam & btlprm );

		//入力更新
		void UpdateInput ( P_CharaInput p );

		//ゲージ類更新
		void UpdateGauge ( BtlParam btlPrm );

		//ヒット数更新
		void UpdateChainHitNum ( UINT n );
	};


	using P_DispChara = std::shared_ptr < DispChara >;


}	//namespace GAME


