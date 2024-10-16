//=================================================================================================
//
//	Script ヘッダファイル
//		毎フレームに処理する値
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
//#include "Define.h"
#include "Define_Siv3D.h"

#include "Rect.h"
#include "Chara_Const.h"
#include "Route.h"
#include "EffectGenerate.h"
#include "ScriptParam_Battle.h"
#include "ScriptParam_Staging.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	//================================================================
	//	◆スクリプト		キャラにおけるアクションの１フレームの値
	//		┣フレーム数
	//		┣イメージID
	//		┣画像表示位置
	//		┣計算状態(持続/代入/加算)
	//		┣[]ルート
	//		┣[]接触枠
	//		┣[]攻撃枠
	//		┣[]当り枠
	//		┣[]相殺枠
	//		┣[]エフェクト発生
	//
	//================================================================

	//クラス
	class Script
	{
		UINT	m_frame {0};		//自身の該当フレーム数
		UINT	m_imageIndex {0};	//イメージID
		VEC2	m_pos {0, 0};		//画像表示位置

		PV_RECT	m_pvCRect;		//接触枠リスト
		PV_RECT	m_pvARect;		//攻撃枠リスト
		PV_RECT	m_pvHRect;		//当り枠リスト
		PV_RECT	m_pvORect;		//相殺枠リスト

		V_UINT		m_vRouteID;		//ルートリスト
		PVP_EfGnrt	m_pvpEfGnrt;	//Efジェネレートリスト

	public:

		//値
		ScriptParam_Battle		m_prmBattle;	//戦闘パラメータ
		ScriptParam_Staging		m_prmStaging;	//演出パラメータ
		s3d::Array < int >		m_versatile;	//汎用パラメータ


		Script ();
		Script ( const Script & rhs ) = delete;
		~Script ();

		void Make ();
		void Rele ();

		//該当フレーム数
		void SetFrame ( UINT frame ) { m_frame = frame; }
		UINT GetFrame () const { return m_frame; }

		//イメージID
		void SetImageIndex ( UINT index ) { m_imageIndex = index; }
		UINT GetImageIndex () const { return m_imageIndex; }

		//画像表示位置
		void SetPos ( VEC2 pos ) { m_pos = pos; }
		VEC2 GetPos () const { return m_pos; }

		//ルート
		void AddRouteID ( UINT i ) { m_vRouteID.push_back ( i ); }
		void SetRouteID ( std::unique_ptr < UINT[] > up_aryUint, UINT size );
		const V_UINT & GetcvRouteID () const { return m_vRouteID; }
		V_UINT & GetvRouteID () { return m_vRouteID; }

		//EfGnrtリスト
		PVP_EfGnrt GetpvpEfGnrt () const { return m_pvpEfGnrt; }

		//EfGnrtリストに追加
		void AddpEfGnrt ( P_EfGnrt pEfGnrt ) { m_pvpEfGnrt->push_back ( pEfGnrt ); }

		//接触枠, 攻撃枠, 当り枠, 相殺枠
		PV_RECT GetpvCRect () const { return m_pvCRect; }
		PV_RECT GetpvARect () const { return m_pvARect; }
		PV_RECT GetpvHRect () const { return m_pvHRect; }
		PV_RECT GetpvORect () const { return m_pvORect; }
		void AddCRect ( RECT crect ) { m_pvCRect->push_back ( crect ); }
		void AddARect ( RECT arect ) { m_pvARect->push_back ( arect ); }
		void AddHRect ( RECT hrect ) { m_pvHRect->push_back ( hrect ); }
		void AddORect ( RECT orect ) { m_pvORect->push_back ( orect ); }
	};


	using P_Script = std::shared_ptr < Script >;
	using VP_Script = std::vector < P_Script >;
	using PVP_Script = std::shared_ptr < VP_Script >;

	//P_Scriptの配列
	using AUP_P_Script = std::unique_ptr < P_Script [] >;


	//s3d
	using Ary_Scp = s3d::Array < Script >;
	using AP_Scp = s3d::Array < P_Script >;
	using PAP_Scp = std::shared_ptr < AP_Scp >;


}	//namespace GAME


