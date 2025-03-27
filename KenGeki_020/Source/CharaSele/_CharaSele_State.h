//=================================================================================================
//
//	_CharaSele_State
//
//=================================================================================================
#pragma once

//-------------------------------------------------------------------------------------------------
// ヘッダファイルのインクルード
//-------------------------------------------------------------------------------------------------
#include "Game.h"

//-------------------------------------------------------------------------------------------------
// 宣言
//-------------------------------------------------------------------------------------------------
namespace GAME
{

	//=====================================================
	//基本ステート
	class _CharaSele_State	: public GameTaskVector
	{

	public:
		_CharaSele_State () {}
		_CharaSele_State ( const _CharaSele_State & rhs ) = delete;
		~_CharaSele_State () {}

		void Input () {}
	};

	using ChSl_St = _CharaSele_State;
	using P_ChSl_St = std::shared_ptr < ChSl_St >;


	//=====================================================

	//キャラクタ選択
	class ChSl_St_Chara : public ChSl_St
	{
	public:
		void Input ();
	};
	using P_ChSlSt_Ch = std::shared_ptr < ChSl_St_Chara >;


	//カラー選択
	class ChSl_St_Color : public ChSl_St
	{
	public:
		void Input ();
	};
	using P_ChSlSt_Clr = std::shared_ptr < ChSl_St_Color >;


	//ステージ選択
	class ChSl_St_Stage : public ChSl_St
	{
	public:
		void Input ();
	};
	using P_ChSlSt_Stg = std::shared_ptr < ChSl_St_Stage >;


	//BGM選択
	class ChSl_St_BGM : public ChSl_St
	{
	public:
		void Input ();
	};
	using P_ChSlSt_BGM = std::shared_ptr < ChSl_St_BGM >;


	//選択完了
	class ChSl_St_OK : public ChSl_St
	{
	public:
		void Input ();
	};
	using P_ChSlSt_OK = std::shared_ptr < ChSl_St_OK >;



}	//namespace GAME

