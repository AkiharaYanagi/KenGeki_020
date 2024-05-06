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
#include "DispMainImage.h"
#if 0
#include "Chara.h"
#include "../../GameMain/GameConst.h"
#include "../../FtgMain/G_Ftg.h"
#include "../../GameMain/Param.h"
#include "DispRect.h"
#include "DispFrontEnd.h"
#include "DispInput.h"
#endif // 0


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class DispChara : public TASK_VEC
	{
		P_DispMainImage	m_mainImage;	//メインイメージ
#if 0
		P_DispRect		m_dispRect;		//枠
		P_GrpAcv		m_grpShadow;	//影
		P_DispFrontEnd	m_frontEnd;		//フロントエンド
		P_DispInput		m_dispInput;	//入力表示

#endif // 0

	public:
		DispChara ();
		DispChara ( const DispChara & rhs ) = delete;
		~DispChara ();

#if 0
		void ParamInit ( P_Param pParam );


		//キャラを設定する
		void SetpChara ( const P_Chara pChara );

		//表示枠設定
		void SetpCharaRect ( P_CharaRect pCharaRect );
#endif // 0

		//更新
//		void Update ( P_Action pAct, P_Script pScp, const BtlParam & btlprm, P_CharaInput pChIpt );
		void Update ();

#if 0
		//------------------------------------------------
		//@info 表示切替
		//  ExeChara以下で行うと1P2Pで2回呼ばれるのでMutualCharaなどで呼び出す
		
		void OnRect () { m_dispRect->OnRect (); }		//枠表示ON
		void OffRect () { m_dispRect->OffRect (); }		//枠表示OFF

		void OnInput () { m_dispInput->On (); }
		void OffInput () { m_dispInput->Off (); }

		void OnFrontEnd () { m_frontEnd->On (); }
		void OffFrontEnd () { m_frontEnd->Off (); }

		//------------------------------------------------

		//PLAYER / CPU
		void SetControl_PLAYER () { m_frontEnd->SetPlayer (); }
		void SetControl_CPU () { m_frontEnd->SetCPU (); }

		//ゲージ類の表示部のみ初期化
		void LoadPlayer ( PLAYER_ID playerID );


		//色変更
		void SetColor ( _CLR clr ) { m_mainImage->SetColor ( clr ); }

		//影化
		void TurnShadow ( bool b ) { m_mainImage->TurnShade ( b ); }


	private:
		//メインイメージの更新
		void UpdateMainImage ( P_Script pScript, VEC2 ptChara, bool dirRight );

		//ゲージ類更新
		void UpdateGauge ( BtlParam btlPrm );

		//入力更新
		void UpdateInput ( P_CharaInput p ) { m_dispInput->UpdateInput ( p ); }

		//ヒット数更新
		void UpdateChainHitNum ( UINT n );
#endif // 0
	};


	using P_DispChara = std::shared_ptr < DispChara >;


}	//namespace GAME


