﻿//=================================================================================================
//
//	_BG ヘッダファイル
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
	class _BG : public TASK_VEC
	{

	public:
		_BG ();
		_BG ( const _BG & rhs ) = delete;
		~_BG ();
	};

	using _P_BG = std::shared_ptr < _BG >;


}	//namespace GAME


