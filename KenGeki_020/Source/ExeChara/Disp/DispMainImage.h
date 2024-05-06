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
#if 0


#include "Chara.h"
#include "../../FtgMain/G_Ftg.h"

#endif // 0
//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//キャラにおけるメインイメージの表示
	//テクスチャをキャラデータから用いる


	class DispMainImage : public TASK_VEC
	{
#if 0
		P_GrpApTx	m_mainGraphic;		//メイングラフィック表示
		PVP_TxBs	m_pvpMainTexture;	//メインイメージのテクスチャリスト

#endif // 0

		P_Grp	m_grp;

	public:
		DispMainImage ();
		DispMainImage ( const DispMainImage & rhs ) = delete;
		~DispMainImage ();

		void Update ();

#if 0
		//元データの設定
		void SetpChara ( P_Chara pChara );

		//メインイメージの更新
		void UpdateMainImage ( P_Script pScript, VEC2 ptChara, bool dirRight );

		//カラー変更
		void SetColor ( _CLR clr ) { m_mainGraphic->SetColor ( clr ); }

		//影化
		void TurnShade ( bool b );

#endif // 0
	};

	using P_DispMainImage = std::shared_ptr < DispMainImage >;


}	//namespace GAME


