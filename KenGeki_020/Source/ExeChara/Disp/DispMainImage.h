//=================================================================================================
//
// DispMainImage ヘッダファイル
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "Chara.h"
#include "../BtlParam.h"
#include "../../FtgMain/G_Ftg.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//キャラにおけるメインイメージの表示
	//テクスチャをキャラデータから用いる


	class DispMainImage : public TASK_VEC
	{
//		P_GrpApTx	m_mainGraphic;		//メイングラフィック表示
		P_Grp		m_mainGraphic;		//メイングラフィック表示
#if 0
		PVP_TxBs	m_pvpMainTexture;	//メインイメージのテクスチャリスト
#endif // 0
		PAP_Tx		mpap_Tx;

		P_Grp	m_grp;

	public:
		DispMainImage ();
		DispMainImage ( const DispMainImage & rhs ) = delete;
		~DispMainImage ();

		//元データの設定
		void SetpChara ( P_Chara pChara );

		//メインイメージの更新
		void UpdateMainImage ( P_Script pScript, const BtlParam & btlprm );

		//カラー変更
		void SetColor ( _CLR clr )
		{
		//	m_mainGraphic->SetColor ( clr );
		}

		//影化
		void TurnShade ( bool b );

	};

	using P_DispMainImage = std::shared_ptr < DispMainImage >;


}	//namespace GAME


