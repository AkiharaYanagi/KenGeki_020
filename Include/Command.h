//=================================================================================================
//
// Command ヘッダファイル
//	ゲーム入力キーの配列を特定の組み合わせで保持する
//	実際に入力されたものの記録と、スクリプト分岐の条件に用いる
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
//#include "Game.h"
#include "Define.h"
#include "Define_Siv3D.h"
#include "GameKeyCommand.h"


//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{
	enum Command_Const
	{
		LMT_DFLT = 16,	//入力受付初期値
	};


	class Command
	{
//		tstring			m_name;				//名前
		s3d::String		m_name { U"" };		//名前
		V_GAME_KEY_CMD	m_vecGameKey;		//キー配列
		UINT			m_limitTime { LMT_DFLT };	//入力受付時間

	public:
		Command ();
		Command ( const Command & rhs ) = delete;	//コピー禁止
		~Command ();

		//比較
		bool Compare ( const V_GAME_KEY & vecGameKey, bool dirRight );

		//名前
//		tstring GetName () const { return m_name; }
//		void SetName ( tstring name ) { m_name.assign ( name ); }
		s3d::String		GetName () const { return m_name; }
		void SetName ( s3d::String name ) { m_name.assign ( name ); }

		//キー配列
		void AddGameKey ( GameKeyCommand gkc ) { m_vecGameKey.push_back ( gkc ); }
		void SetaGameKey ( GameKeyCommand gkca [], UINT size );

		//入力受付時間
		UINT GetLimitTime () const { return m_limitTime; }
		void SetLimitTime ( UINT limitTime ) { m_limitTime = limitTime; }
	};

//	using WP_Command = std::weak_ptr < Command >;
	using P_Command = std::shared_ptr < Command >;
	using VP_Command = std::vector < P_Command >;

}	//namespace GAME


