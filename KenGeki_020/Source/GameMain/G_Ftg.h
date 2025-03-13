//=================================================================================================
//
//	G_Ftg ヘッダファイル
//		Fighting共通グローバル変数群
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"
#include "../GameMain/GameConst.h"
//#include "FtgConst.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	class G_Ftg
	{
	//---------------------------------------------------------------------
	//シングルトンパターン
	private:
		using  _P_G_Ftg = std::unique_ptr < G_Ftg >;
		static _P_G_Ftg m_inst;		//シングルトンインスタンス
		G_Ftg ();		//private コンストラクタで通常の実体化は禁止
	public:
		~G_Ftg ();		//デストラクタはunique_ptrのためpublic
		static void Create() { if ( ! m_inst ) { m_inst = _P_G_Ftg ( new G_Ftg () ); } }
		static _P_G_Ftg & inst () { return m_inst; }	//インスタンス取得
	//---------------------------------------------------------------------

	private:
		//キャラ中央位置(ゲーム位置)
		float	m_chara_center_x { 0 };

		//壁位置 (ゲーム範囲からの算出)(ゲーム位置)
		float	m_wall_L { 0 };	//左
		float	m_wall_R { 0 };	//右

		//画面端位置 (キャラ中心からの算出)(ゲーム位置)
		float	m_edge_L { 0 };
		float	m_edge_R { 0 };

		//キャラ位置による画面補正量(表示位置)
		VEC2	m_posMutualBase { 0, 0 };

		//立ち位置リセットフラグ
		//条件：画面端で "足払い" がヒット時
		//効果：背景を中央に移動する
		bool	m_bResetPos { F };
//		Timer	m_tmr_resetPos;
		float	m_vel_resetPos { 10.f };

		//壁移動中
		bool	m_bWallMove { F };

		//システム表示
		bool	m_sysDisp { T };

	public:
		//初期化
		void Init ();


		//キャラ中央位置(ゲーム位置)
		float GetCharaCenterX () const { return m_chara_center_x; }

		//画面端での表示基準位置
		void CulcPosMutualBase ( VEC2 pos1p, VEC2 pos2p );
		VEC2 GetPosMutualBase () const { return m_posMutualBase; }

		//新規壁位置設定フラグ
		bool GetNewWall () const
		{ return m_bResetPos; }
		void SetNewWall ( bool b ) { m_bResetPos = b; }
		void SetResetPos ( bool b ) { m_bResetPos = b; }

		void ResetWall ();

		//壁位置
		float GetWallLeft () const { return m_wall_L; }
		float GetWallRight () const { return m_wall_R; }

		void SetWallMove ( bool b ) { m_bWallMove = b; }

		//画面端位置
		float GetEdgeLeft () const { return m_edge_L; }
		float GetEdgeRight () const { return m_edge_R; }

		//システム表示
		GET_SET ( bool, GetSysDisp, SetSysDisp, m_sysDisp )


	private:
		//カメラの画面端における補正位置
		void RevisedCamera ( VEC2 pos1p, VEC2 pos2p );
	};

	using  UP_G_Ftg = std::unique_ptr < G_Ftg >;


#define G_FTG	G_Ftg::inst
#define G_BASE_POS	G_Ftg::inst()->GetPosMutualBase


}	//namespace GAME


