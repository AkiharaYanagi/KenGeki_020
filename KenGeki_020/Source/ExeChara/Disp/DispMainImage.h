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


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//キャラにおけるメインイメージの表示
	//テクスチャをキャラデータから用いる


	class DispMainImage : public TASK_VEC
	{
		P_Grp		m_mainGraphic;		//メイングラフィック表示
		PAP_Tx		mpap_Tx;	//メインイメージのテクスチャリスト

		P_Grp		m_grpShadow;	//影

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
			(void)clr;
		//	m_mainGraphic->SetColor ( clr );
		}

		//影化
		void TurnShadow ( bool b );

		//乗算カラー指定
		void SetColor ( uint32 clr );

		//メインイメージを同一Z値で先頭にする
		void TopByZ ();

		//影を消す
		void OffShade() { m_grpShadow->SetValid ( F ); }

		//影を表示する
		void OnShade() { m_grpShadow->SetValid ( T ); }

	};

	using P_DispMainImage = std::shared_ptr < DispMainImage >;


}	//namespace GAME


