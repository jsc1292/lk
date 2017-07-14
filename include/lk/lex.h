#ifndef __lk_lex_h
#define __lk_lex_h

#include <cstdio>

#include <lk/absyn.h>

namespace lk {

/** 
 * \class input_base
 *
 * This class stores input script as lk_strings (wxstring).
 *
 * For proper compilation: 
 * Define _WIN32 if on Windows
 * Define _DEBUG if compile with debugging
 *
 */
	class input_base
	{
	public:
		virtual ~input_base() { }
		virtual char operator*() = 0;
		virtual char peek() = 0;
		virtual char operator++(int) = 0;
	};
		
	class input_string : public input_base
	{
	protected:
		char *m_buf;
		char *m_p;
		bool allocate( size_t n );
	public:
		input_string();
		input_string( const lk_string &in );
		virtual ~input_string();
		virtual char operator*();
		virtual char operator++(int);
		virtual char peek();
	};

	class input_file : public input_string
	{
	public:
		input_file( const lk_string &file );
		virtual ~input_file();
	};
	

/** 
 * \class lexer
 *
 * Lexer takes as input an input_base and extracts tokens from the input LK string
 * by identifying the structural pieces of the language. Lexer changes state as it
 * traverses the input string when next() is called: the token type is returned and
 * m_buf stores the string literal of the current token, which is accessed through text().
 *
 */

	class lexer
	{
	public:
		static const char *tokstr(int t);

		enum {
			INVALID,
			END,
			IDENTIFIER,
			SPECIAL,
			NUMBER,
			LITERAL,

			// one character tokens
			SEP_SEMI,		// ;
			SEP_COLON,		// :
			SEP_COMMA,		// ,
			SEP_LPAREN,		// (
			SEP_RPAREN,		// )
			SEP_LCURLY,		// {
			SEP_RCURLY,		// }
			SEP_LBRACK,		// [
			SEP_RBRACK,		// ]

			OP_PLUS,		// +
			OP_MINUS,		// -
			OP_MULT,		// *
			OP_DIV,			// /
			OP_EXP,			// ^
			OP_DOT,			// .
			OP_QMARK,		// ?
			OP_QMARKAT,		// ?@
			OP_POUND,		// #
			OP_TILDE,		// ~
			OP_PERCENT,		// %
			OP_AT,			// @
			OP_LOGIAND,		// &&
			OP_LOGIOR,		// ||
			OP_BITAND,		// &
			OP_BITOR,		// |
			OP_BANG,		// !
			OP_ASSIGN,		// =
			OP_REF,			// ->
			OP_PP,			// ++
			OP_MM,			// --
			OP_LT,			// <
			OP_GT,			// >
			OP_EQ,			// ==
			OP_NE,			// !=
			OP_LE,			// <=
			OP_GE,			// >=
			OP_PLUSEQ,		// +=
			OP_MINUSEQ,		// -=
			OP_MULTEQ,		// *=
			OP_DIVEQ,		// /=
			OP_MINUSAT		// -@

		};

		lexer( input_base &input );

		int next();
		
		lk_string text();
		double value();

		int line();
		lk_string error();

	private:
		void whitespace();
		bool comments();

		lk_string m_error;
		int m_line;
		lk_string m_buf;
		double m_val;
		
		input_base &p;
	};
};

#endif
