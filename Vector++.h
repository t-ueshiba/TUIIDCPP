/*
 *  $BJ?@.(B9$BG/(B $BEE;R5;=QAm9g8&5f=j(B $B?"<G=SIW(B $BCx:n8"=jM-(B
 *
 *  $BCx:n<T$K$h$k5v2D$J$7$K$3$N%W%m%0%i%`$NBh;0<T$X$N3+<(!"J#@=!"2~JQ!"(B
 *  $B;HMQEy$=$NB>$NCx:n?M3J8"$r?/32$9$k9T0Y$r6X;_$7$^$9!#(B
 *  $B$3$N%W%m%0%i%`$K$h$C$F@8$8$k$$$+$J$kB;32$KBP$7$F$b!"Cx:n<T$O@UG$(B
 *  $B$rIi$$$^$;$s!#(B 
 *
 *
 *  Copyright 1996
 *  Toshio UESHIBA, Electrotechnical Laboratory
 *
 *  All rights reserved.
 *  Any changing, copying or giving information about source programs of
 *  any part of this software and/or documentation without permission of the
 *  authors are prohibited.
 *
 *  No Warranty.
 *  Authors are not responsible for any damage in use of this program.
 */

/*
 *  $Id: Vector++.h,v 1.18 2007-02-28 00:16:06 ueshiba Exp $
 */
#ifndef __TUVectorPP_h
#define __TUVectorPP_h

#include <cmath>
#ifdef WIN32
#  define M_PI	3.14159265358979323846
#endif
#include "TU/Array++.h"

namespace TU
{
/************************************************************************
*  class Rotation							*
************************************************************************/
//! 2$B<!85D6J?LLFb$G$N2sE>$rI=$9%/%i%9(B
/*!
  $B6qBNE*$K$O(B
  \f[
    \TUvec{R}{}(p, q; \theta) \equiv
    \begin{array}{r@{}l}
      & \begin{array}{ccccccccccc}
        & & \makebox[4.0em]{} & p & & & \makebox[3.8em]{} & q & & &
      \end{array} \\
      \begin{array}{l}
        \\ \\ \\ \raisebox{1.5ex}{$p$} \\ \\ \\ \\ \raisebox{1.5ex}{$q$} \\ \\ \\
      \end{array} &
      \TUbeginarray{ccccccccccc}
	1 \\
	& \ddots \\
	& & 1 \\
	& & & \cos\theta & & & & -\sin\theta \\
	& & & & 1 \\
	& & & & & \ddots \\
	& & & & & & 1 \\
	& & & \sin\theta & & & & \cos\theta \\
	& & & & & & & & 1\\
	& & & & & & & & & \ddots \\
	& & & & & & & & & & 1
      \TUendarray
    \end{array}
  \f]
  $B$J$k2sE>9TNs$GI=$5$l$k!%(B
*/
class Rotation
{
  public:
    Rotation(int p, int q, double x, double y)		;
    Rotation(int p, int q, double theta)		;

  //! p$B<4$rJV$9!%(B
  /*!
    \return	p$B<4$N(Bindex
  */
    int		p()				const	{return _p;}

  //! q$B<4$rJV$9!%(B
  /*!
    \return	q$B<4$N(Bindex
  */
    int		q()				const	{return _q;}

  //! $B2sE>3Q@8@.%Y%/%H%k$ND9$5$rJV$9!%(B
  /*!
    \return	$B2sE>3Q@8@.%Y%/%H%k(B(x, y)$B$KBP$7$F(B\f$\sqrt{x^2 + y^2}\f$
  */
    double	length()			const	{return _l;}

  //! $B2sE>3Q$N(Bcos$BCM$rJV$9!%(B
  /*!
    \return	$B2sE>3Q$N(Bcos$BCM(B
  */
    double	cos()				const	{return _c;}

  //! $B2sE>3Q$N(Bsin$BCM$rJV$9!%(B
  /*!
    \return	$B2sE>3Q$N(Bsin$BCM(B
  */
    double	sin()				const	{return _s;}
    
  private:
    const int	_p, _q;				// rotation axis
    double	_l;				// length of (x, y)
    double	_c, _s;				// cos & sin
};

/************************************************************************
*  class Vector<T>							*
************************************************************************/
template <class T>	class Matrix;

//! T$B7?$NMWAG$r;}$D%Y%/%H%k$rI=$9%/%i%9(B
template <class T, class B=Buf<T> >
class Vector : public Array<T, B>
{
  public:
    typedef typename Array<T, B>::value_type		value_type;
    typedef typename Array<T, B>::difference_type	difference_type;
    typedef typename Array<T, B>::reference		reference;
    typedef typename Array<T, B>::const_reference	const_reference;
    typedef typename Array<T, B>::pointer		pointer;
    typedef typename Array<T, B>::const_pointer		const_pointer;
    typedef typename Array<T, B>::iterator		iterator;
    typedef typename Array<T, B>::const_iterator	const_iterator;
    
  public:
    Vector()								;
    explicit Vector(u_int d)						;
    Vector(T* p, u_int d)						;
    Vector(const Matrix<T>& m)						;
    template <class B2>
    Vector(const Vector<T, B2>& v, int i, u_int d)			;
    template <class T2, class B2>
    Vector(const Vector<T2, B2>& v)					;
    template <class T2, class B2>
    Vector&		operator =(const Vector<T2, B2>& v)		;

    using		Array<T, B>::begin;
    using		Array<T, B>::end;
    using		Array<T, B>::size;
    using		Array<T, B>::dim;
    using		Array<T, B>::operator pointer;
    using		Array<T, B>::operator const_pointer;

    const Vector<T>	operator ()(int i, u_int d)		const	;
    Vector<T>		operator ()(int i, u_int d)			;
    Vector&		operator  =(T c)				;
    Vector&		operator *=(double c)				;
    Vector&		operator /=(double c)				;
    template <class T2, class B2>
    Vector&		operator +=(const Vector<T2, B2>& v)		;
    template <class T2, class B2>
    Vector&		operator -=(const Vector<T2, B2>& v)		;
    template <class T2, class B2>
    Vector&		operator ^=(const Vector<T2, B2>& V)		;
    template <class T2>
    Vector&		operator *=(const Matrix<T2>& m)		;
    Vector		operator  -()				const	;
    T			square()				const	;
    T			length()				const	;
    template <class T2, class B2>
    T			sqdist(const Vector<T2, B2>& v)		const	;
    template <class T2, class B2>
    T			dist(const Vector<T2, B2>& v)		const	;
    Vector&		normalize()					;
    Vector		normal()				const	;
    template <class T2>
    Vector&		solve(const Matrix<T2>& m)			;
    Matrix<T>		skew()					const	;
    void		resize(u_int d)					;
    void		resize(T* p, u_int d)				;
};

//! $B%Y%/%H%k$r@8@.$7!$A4MWAG$r(B0$B$G=i4|2=$9$k!%(B
template <class T, class B>
Vector<T, B>::Vector()
    :Array<T, B>()
{
    *this = 0;
}

//! $B;XDj$5$l$?<!85$N%Y%/%H%k$r@8@.$7!$A4MWAG$r(B0$B$G=i4|2=$9$k!%(B
/*!
  \param d	$B%Y%/%H%k$N<!85(B
*/
template <class T, class B> inline
Vector<T, B>::Vector(u_int d)
    :Array<T, B>(d)
{
    *this = 0;
}

//! $B30It5-21NN0h$H<!85$r;XDj$7$F%Y%/%H%k$r@8@.$9$k!%(B
/*!
  \param p	$B30It5-21NN0h$X$N%]%$%s%?(B
  \param d	$B%Y%/%H%k$N<!85(B
*/
template <class T, class B> inline
Vector<T, B>::Vector(T* p, u_int d)
    :Array<T, B>(p, d)
{
}

//! $BM?$($i$l$?9TNs$N9T$rJB$Y$F5-21NN0h$r6&M-$9$k%Y%/%H%k$r@8@.$9$k!%(B
/*!
  \param m	$B5-21NN0h$r6&M-$9$k9TNs!%A49T$N5-21NN0h$OO"B3$7$F$$$J$1$l$P(B
		$B$J$i$J$$!%(B
*/
template <class T, class B> inline
Vector<T, B>::Vector(const Matrix<T>& m)
    :Array<T, B>(const_cast<T*>((const T*)m), m.nrow()*m.ncol())
{
}

//! $BM?$($i$l$?%Y%/%H%k$H5-21NN0h$r6&M-$9$kItJ,%Y%/%H%k$r@8@.$9$k!%(B
/*!
  \param v	$B85$N%Y%/%H%k(B
  \param i	$BItJ,%Y%/%H%k$NBh(B0$BMWAG$r;XDj$9$k(Bindex
  \param d	$BItJ,%Y%/%H%k$N<!85(B
*/
template <class T, class B> template <class B2> inline
Vector<T, B>::Vector(const Vector<T, B2>& v, int i, u_int d)
    :Array<T, B>(v, i, d)
{
}

//! $BB>$N%Y%/%H%k$HF10lMWAG$r;}$D%Y%/%H%k$r:n$k(B($B%3%T!<%3%s%9%H%i%/%?$N3HD%(B)$B!%(B
/*!
  \param v	$B%3%T!<85%Y%/%H%k(B
*/
template <class T, class B> template <class T2, class B2> inline
Vector<T, B>::Vector(const Vector<T2, B2>& v)
    :Array<T, B>(v)
{
}
    
//! $BB>$N%Y%/%H%k$r<+J,$KBeF~$9$k(B($BBeF~1i;;;R$N3HD%(B)$B!%(B
/*!
  \param v	$B%3%T!<85%Y%/%H%k(B
  \return	$B$3$N%Y%/%H%k(B
*/
template <class T, class B> template <class T2, class B2> inline Vector<T, B>&
Vector<T, B>::operator =(const Vector<T2, B2>& v)
{
    Array<T, B>::operator =(v);
    return *this;
}

//! $B$3$N%Y%/%H%k$H5-21NN0h$r6&M-$7$?ItJ,%Y%/%H%k$r@8@.$9$k!%(B
/*!
    \param i	$BItJ,%Y%/%H%k$NBh(B0$BMWAG$r;XDj$9$k(Bindex
    \param d	$BItJ,%Y%/%H%k$N<!85(B
    \return	$B@8@.$5$l$?ItJ,%Y%/%H%k(B
*/
template <class T, class B> inline Vector<T>
Vector<T, B>::operator ()(int i, u_int d)
{
    return Vector<T>(*this, i, d);
}

//! $B$3$N%Y%/%H%k$H5-21NN0h$r6&M-$7$?ItJ,%Y%/%H%k$r@8@.$9$k!%(B
/*!
    \param i	$BItJ,%Y%/%H%k$NBh(B0$BMWAG$r;XDj$9$k(Bindex
    \param d	$BItJ,%Y%/%H%k$N<!85(B
    \return	$B@8@.$5$l$?ItJ,%Y%/%H%k(B
*/
template <class T, class B> inline const Vector<T>
Vector<T, B>::operator ()(int i, u_int d) const
{
    return Vector<T>(*this, i, d);
}

//! $B$3$N%Y%/%H%k$NA4$F$NMWAG$KF10l$N?tCM$rBeF~$9$k!%(B
/*!
  \param c	$BBeF~$9$k?tCM(B
  \return	$B$3$N%Y%/%H%k(B
*/
template <class T, class B> inline Vector<T, B>&
Vector<T, B>::operator =(T c)
{
    Array<T, B>::operator =(c);
    return *this;
}

//! $B$3$N%Y%/%H%k$K;XDj$5$l$??tCM$r3]$1$k!%(B
/*!
  \param c	$B3]$1$k?tCM(B
  \return	$B$3$N%Y%/%H%k!$$9$J$o$A(B\f$\TUvec{u}{}\leftarrow c\TUvec{u}{}\f$
*/
template <class T, class B> inline Vector<T, B>&
Vector<T, B>::operator *=(double c)
{
    Array<T, B>::operator *=(c);
    return *this;
}

//! $B$3$N%Y%/%H%k$r;XDj$5$l$??tCM$G3d$k!%(B
/*!
  \param c	$B3d$k?tCM(B
  \return	$B$3$N%Y%/%H%k!$$9$J$o$A(B
		\f$\TUvec{u}{}\leftarrow \frac{\TUvec{u}{}}{c}\f$
*/
template <class T, class B> inline Vector<T, B>&
Vector<T, B>::operator /=(double c)
{
    Array<T, B>::operator /=(c);
    return *this;
}

//! $B$3$N%Y%/%H%k$KB>$N%Y%/%H%k$rB-$9!%(B
/*!
  \param v	$BB-$9%Y%/%H%k(B
  \return	$B$3$N%Y%/%H%k!$$9$J$o$A(B
		\f$\TUvec{u}{}\leftarrow \TUvec{u}{} + \TUvec{v}{}\f$
*/
template <class T, class B> template <class T2, class B2> inline Vector<T, B>&
Vector<T, B>::operator +=(const Vector<T2, B2>& v)
{
    Array<T, B>::operator +=(v);
    return *this;
}

//! $B$3$N%Y%/%H%k$+$iB>$N%Y%/%H%k$r0z$/!%(B
/*!
  \param v	$B0z$/%Y%/%H%k(B
  \return	$B$3$N%Y%/%H%k!$$9$J$o$A(B
		\f$\TUvec{u}{}\leftarrow \TUvec{u}{} - \TUvec{v}{}\f$
*/
template <class T, class B> template <class T2, class B2> inline Vector<T, B>&
Vector<T, B>::operator -=(const Vector<T2, B2>& v)
{
    Array<T, B>::operator -=(v);
    return *this;
}

//! $B$3$N%Y%/%H%k$HB>$N(B3$B<!85%Y%/%H%k$H$N%Y%/%H%k@Q$r$H$k!%(B
/*!
    \param v	$BB>$N%Y%/%H%k(B
    \return	$B$3$N%Y%/%H%k!$$9$J$o$A(B
		\f$\TUvec{u}{}\leftarrow \TUvec{u}{}\times\TUvec{v}{}\f$
    \throw std::invalid_argument	$B$3$N%Y%/%H%k$H(Bv$B$,(B3$B<!85$G$J$$>l9g$KAw=P(B
*/
template <class T, class B> template <class T2, class B2> Vector<T, B>&
Vector<T, B>::operator ^=(const Vector<T2, B2>& v)	// outer product
{
    check_dim(v.dim());
    if (dim() != 3)
	throw std::invalid_argument("TU::Vector<T, B>::operator ^=: dimension must be 3");
    Vector<T, FixedSizedBuf<T, 3u> > tmp(*this);
    (*this)[0] = tmp[1] * v[2] - tmp[2] * v[1];
    (*this)[1] = tmp[2] * v[0] - tmp[0] * v[2];
    (*this)[2] = tmp[0] * v[1] - tmp[1] * v[0];
    return *this;
}

//! $B$3$N%Y%/%H%k$N1&$+$i9TNs$r3]$1$k!%(B
/*!
  \param m	$B3]$1$k9TNs(B
  \return	$B$3$N%Y%/%H%k!$$9$J$o$A(B
		\f$\TUtvec{u}{} \leftarrow \TUtvec{u}{}\TUvec{M}{}\f$
*/
template <class T, class B> template <class T2> inline Vector<T, B>&
Vector<T, B>::operator *=(const Matrix<T2>& m)
{
    return *this = *this * m;
}

//! $B$3$N%Y%/%H%k$NId9f$rH?E>$7$?%Y%/%H%k$rJV$9!%(B
/*!
  \return	$BId9f$rH?E>$7$?%Y%/%H%k!$$9$J$o$A(B\f$-\TUvec{u}{}\f$
*/
template <class T, class B> inline Vector<T, B>
Vector<T, B>::operator -() const
{
    return Vector(*this) *= -1;
}

//! $B$3$N%Y%/%H%k$ND9$5$N(B2$B>h$rJV$9!%(B
/*!
  \return	$B%Y%/%H%k$ND9$5$N(B2$B>h!$$9$J$o$A(B\f$\TUnorm{\TUvec{u}{}}^2\f$
*/
template <class T, class B> inline T
Vector<T, B>::square() const
{
    return *this * *this;
}

//! $B$3$N%Y%/%H%k$ND9$5$rJV$9!%(B
/*!
  \return	$B%Y%/%H%k$ND9$5!$$9$J$o$A(B\f$\TUnorm{\TUvec{u}{}}\f$
*/
template <class T, class B> inline T
Vector<T, B>::length() const
{
    return sqrt(square());
}

//! $B$3$N%Y%/%H%k$HB>$N%Y%/%H%k$N:9$ND9$5$N(B2$B>h$rJV$9!%(B
/*!
  \param v	$BHf3SBP>]$H$J$k%Y%/%H%k(B
  \return	$B%Y%/%H%k4V$N:9$N(B2$B>h!$$9$J$o$A(B
		\f$\TUnorm{\TUvec{u}{} - \TUvec{v}{}}^2\f$
*/
template <class T, class B> template <class T2, class B2> inline T
Vector<T, B>::sqdist(const Vector<T2, B2>& v) const
{
    return (*this - v).square();
}

//! $B$3$N%Y%/%H%k$HB>$N%Y%/%H%k$N:9$ND9$5$rJV$9!%(B
/*!
  \param v	$BHf3SBP>]$H$J$k%Y%/%H%k(B
  \return	$B%Y%/%H%k4V$N:9!$$9$J$o$A(B
		\f$\TUnorm{\TUvec{u}{} - \TUvec{v}{}}\f$
*/
template <class T, class B> template <class T2, class B2> inline T
Vector<T, B>::dist(const Vector<T2, B2>& v) const
{
    return sqrt(sqdist(v));
}

//! $B$3$N%Y%/%H%k$ND9$5$r(B1$B$K@55,2=$9$k!%(B
/*!
  \return	$B$3$N%Y%/%H%k!$$9$J$o$A(B
		\f$
		  \TUvec{u}{}\leftarrow\frac{\TUvec{u}{}}{\TUnorm{\TUvec{u}{}}}
		\f$
*/
template <class T, class B> inline Vector<T, B>&
Vector<T, B>::normalize()
{
    return *this /= length();
}

//! $B$3$N%Y%/%H%k$ND9$5$r(B1$B$K@55,2=$7$?%Y%/%H%k$rJV$9!%(B
/*!
  \return	$BD9$5$r@55,2=$7$?%Y%/%H%k!$$9$J$o$A(B
		\f$\frac{\TUvec{u}{}}{\TUnorm{\TUvec{u}{}}}\f$
*/
template <class T, class B> inline Vector<T, B>
Vector<T, B>::normal() const
{
    return Vector(*this).normalize();
}

//! $B%Y%/%H%k$N<!85$rJQ99$7!$A4MWAG$r(B0$B$K=i4|2=$9$k!%(B
/*!
  $B$?$@$7!$B>$N%*%V%8%'%/%H$H5-21NN0h$r6&M-$7$F$$$k%Y%/%H%k$N<!85$r(B
  $BJQ99$9$k$3$H$O$G$-$J$$!%(B
  \param d	$B?7$7$$<!85(B
*/
template <class T, class B> inline void
Vector<T, B>::resize(u_int d)
{
    Array<T, B>::resize(d);
    *this = 0;
}

//! $B%Y%/%H%k$,FbIt$G;HMQ$9$k5-21NN0h$r;XDj$7$?$b$N$KJQ99$9$k!%(B
/*!
  \param p	$B?7$7$$5-21NN0h$X$N%]%$%s%?(B
  \param siz	$B?7$7$$<!85(B
*/
template <class T, class B> inline void
Vector<T, B>::resize(T* p, u_int d)
{
    Array<T, B>::resize(p, d);
}

/************************************************************************
*  class Matrix<T>							*
************************************************************************/
//! T$B7?$NMWAG$r;}$D9TNs$rI=$9%/%i%9(B
/*!
  $B3F9T$,(BT$B7?$NMWAG$r;}$D%Y%/%H%k(B#TU::Vector<T>$B$K$J$C$F$$$k!%(B
*/
template <class T>
class Matrix : public Array2<Vector<T> >
{
  public:
    typedef typename Array2<Vector<T> >::value_type		value_type;
    typedef typename Array2<Vector<T> >::difference_type	difference_type;
    typedef typename Array2<Vector<T> >::reference		reference;
    typedef typename Array2<Vector<T> >::const_reference	const_reference;
    typedef typename Array2<Vector<T> >::pointer		pointer;
    typedef typename Array2<Vector<T> >::const_pointer		const_pointer;
    typedef typename Array2<Vector<T> >::iterator		iterator;
    typedef typename Array2<Vector<T> >::const_iterator		const_iterator;
    
  public:
    explicit Matrix(u_int r=0, u_int c=0)				;
    Matrix(T* p, u_int r, u_int c)					;
    Matrix(const Matrix& m, int i, int j, u_int r, u_int c)		;
    template <class T2>
    Matrix(const Matrix<T2>& m)						;
    template <class T2>
    Matrix&		operator =(const Matrix<T2>& m)			;

    using		Array2<Vector<T> >::begin;
    using		Array2<Vector<T> >::end;
    using		Array2<Vector<T> >::size;
    using		Array2<Vector<T> >::dim;
    using		Array2<Vector<T> >::nrow;
    using		Array2<Vector<T> >::ncol;
    using		Array2<Vector<T> >::operator pointer;
    using		Array2<Vector<T> >::operator const_pointer;
    
    const Matrix	operator ()(int i, int j,
				    u_int r, u_int c)		const	;
    Matrix		operator ()(int i, int j,
				    u_int r, u_int c)			;
    Matrix&		operator  =(T c)				;
    Matrix&		operator *=(double c)				;
    Matrix&		operator /=(double c)				;
    template <class T2>
    Matrix&		operator +=(const Matrix<T2>& m)		;
    template <class T2>
    Matrix&		operator -=(const Matrix<T2>& m)		;
    template <class T2>
    Matrix&		operator *=(const Matrix<T2>& m)		;
    template <class T2, class B2>
    Matrix&		operator ^=(const Vector<T2, B2>& v)		;
    Matrix		operator  -()				const	;
    Matrix&		diag(T c)					;
    Matrix		trns()					const	;
    Matrix		inv()					const	;
    template <class T2>
    Matrix&		solve(const Matrix<T2>&)			;
    T			det()					const	;
    T			det(int p, int q)			const	;
    T			trace()					const	;
    Matrix		adj()					const	;
    Matrix		pinv(T cndnum=1.0e5)			const	;
    Matrix		eigen(Vector<T>& eval)			const	;
    Matrix		geigen(const Matrix<T>& B,
			       Vector<T>& eval)			const	;
    Matrix		cholesky()				const	;
    Matrix&		normalize()					;
    Matrix&		rotate_from_left(const Rotation& r)		;
    Matrix&		rotate_from_right(const Rotation& r)		;
    T			square()				const	;
    T			length()				const	;
    Matrix&		symmetrize()					;
    Matrix&		antisymmetrize()				;
    void		rot2angle(T& theta_x,
				  T& theta_y, T& theta_z)	const	;
    Vector<T, FixedSizedBuf<T, 3> >
			rot2axis(T& c, T& s)	const	;
    Vector<T, FixedSizedBuf<T, 3> >
			rot2axis()				const	;

    static Matrix	I(u_int d)					;
    template <class T2, class B2>
    static Matrix	Rt(const Vector<T2, B2>& n, T c, T s)		;
    template <class T2, class B2>
    static Matrix	Rt(const Vector<T2, B2>& axis)			;

    void		resize(u_int r, u_int c)			;
    void		resize(T* p, u_int r, u_int c)			;
};

//! $B;XDj$5$l$?%5%$%:$N9TNs$r@8@.$7!$A4MWAG$r(B0$B$G=i4|2=$9$k!%(B
/*!
  \param r	$B9TNs$N9T?t(B
  \param c	$B9TNs$NNs?t(B
*/
template <class T> inline
Matrix<T>::Matrix(u_int r, u_int c)
    :Array2<Vector<T> >(r, c)
{
    *this = 0;
}

//! $B30It5-21NN0h$H%5%$%:$r;XDj$7$F9TNs$r@8@.$9$k!%(B
/*!
  \param p	$B30It5-21NN0h$X$N%]%$%s%?(B
  \param r	$B9TNs$N9T?t(B
  \param c	$B9TNs$NNs?t(B
*/
template <class T> inline
Matrix<T>::Matrix(T* p, u_int r, u_int c)
    :Array2<Vector<T> >(p, r, c)
{
}

//! $BM?$($i$l$?9TNs$H5-21NN0h$r6&M-$9$kItJ,9TNs$r@8@.$9$k!%(B
/*!
  \param m	$B85$N9TNs(B
  \param i	$BItJ,9TNs$NBh(B0$B9T$r;XDj$9$k(Bindex
  \param j	$BItJ,9TNs$NBh(B0$BNs$r;XDj$9$k(Bindex
  \param r	$BItJ,9TNs$N9T?t(B
  \param c	$BItJ,9TNs$NNs?t(B
*/
template <class T> inline
Matrix<T>::Matrix(const Matrix& m, int i, int j, u_int r, u_int c)
    :Array2<Vector<T> >(m, i, j, r, c)
{
}

//! $BB>$N9TNs$HF10lMWAG$r;}$D9TNs$r:n$k(B($B%3%T!<%3%s%9%H%i%/%?$N3HD%(B)$B!%(B
/*!
  \param m	$B%3%T!<859TNs(B
*/
template <class T> template <class T2> inline
Matrix<T>::Matrix(const Matrix<T2>& m)
    :Array2<Vector<T> >(m)
{
}

//! $BB>$N9TNs$r<+J,$KBeF~$9$k(B($BBeF~1i;;;R$N3HD%(B)$B!%(B
/*!
  \param m	$B%3%T!<859TNs(B
  \return	$B$3$N9TNs(B
*/
template <class T> template <class T2> inline Matrix<T>&
Matrix<T>::operator =(const Matrix<T2>& m)
{
    Array2<Vector<T> >::operator =(m);
    return *this;
}

//! $B$3$N9TNs$H5-21NN0h$r6&M-$7$?ItJ,9TNs$r@8@.$9$k!%(B
/*!
    \param i	$BItJ,9TNs$N:8>e6yMWAG$H$J$k9T$r;XDj$9$k(Bindex
    \param j	$BItJ,9TNs$N:8>e6yMWAG$H$J$kNs$r;XDj$9$k(Bindex
    \param r	$BItJ,9TNs$N9T?t(B
    \param c	$BItJ,9TNs$NNs?t(B
    \return	$B@8@.$5$l$?ItJ,9TNs(B
*/
template <class T> inline Matrix<T>
Matrix<T>::operator ()(int i, int j, u_int r, u_int c)
{
    return Matrix<T>(*this, i, j, r, c);
}

//! $B$3$N9TNs$H5-21NN0h$r6&M-$7$?ItJ,9TNs$r@8@.$9$k!%(B
/*!
    \param i	$BItJ,9TNs$N:8>e6yMWAG$H$J$k9T$r;XDj$9$k(Bindex
    \param j	$BItJ,9TNs$N:8>e6yMWAG$H$J$kNs$r;XDj$9$k(Bindex
    \param r	$BItJ,9TNs$N9T?t(B
    \param c	$BItJ,9TNs$NNs?t(B
    \return	$B@8@.$5$l$?ItJ,9TNs(B
*/
template <class T> inline const Matrix<T>
Matrix<T>::operator ()(int i, int j, u_int r, u_int c) const
{
    return Matrix<T>(*this, i, j, r, c);
}

//! $B$3$N9TNs$NA4$F$NMWAG$KF10l$N?tCM$rBeF~$9$k!%(B
/*!
  \param c	$BBeF~$9$k?tCM(B
  \return	$B$3$N9TNs(B
*/
template <class T> inline Matrix<T>&
Matrix<T>::operator =(T c)
{
    Array2<Vector<T> >::operator =(c);
    return *this;
}

//! $B$3$N9TNs$K;XDj$5$l$??tCM$r3]$1$k!%(B
/*!
  \param c	$B3]$1$k?tCM(B
  \return	$B$3$N9TNs!$$9$J$o$A(B\f$\TUvec{A}{}\leftarrow c\TUvec{A}{}\f$
*/
template <class T> inline Matrix<T>&
Matrix<T>::operator *=(double c)
{
    Array2<Vector<T> >::operator *=(c);
    return *this;
}

//! $B$3$N9TNs$r;XDj$5$l$??tCM$G3d$k!%(B
/*!
  \param c	$B3d$k?tCM(B
  \return	$B$3$N9TNs!$$9$J$o$A(B
		\f$\TUvec{A}{}\leftarrow \frac{\TUvec{A}{}}{c}\f$
*/
template <class T> inline Matrix<T>&
Matrix<T>::operator /=(double c)
{
    Array2<Vector<T> >::operator /=(c);
    return *this;
}

//! $B$3$N9TNs$KB>$N9TNs$rB-$9!%(B
/*!
  \param m	$BB-$99TNs(B
  \return	$B$3$N9TNs!$$9$J$o$A(B
		\f$\TUvec{A}{}\leftarrow \TUvec{A}{} + \TUvec{M}{}\f$
*/
template <class T> template <class T2> inline Matrix<T>&
Matrix<T>::operator +=(const Matrix<T2>& m)
{
    Array2<Vector<T> >::operator +=(m);
    return *this;
}

//! $B$3$N9TNs$+$iB>$N9TNs$r0z$/!%(B
/*!
  \param m	$B0z$/9TNs(B
  \return	$B$3$N9TNs!$$9$J$o$A(B
		\f$\TUvec{A}{}\leftarrow \TUvec{A}{} - \TUvec{M}{}\f$
*/
template <class T> template <class T2> inline Matrix<T>&
Matrix<T>::operator -=(const Matrix<T2>& m)
{
    Array2<Vector<T> >::operator -=(m);
    return *this;
}

//! $B$3$N9TNs$KB>$N9TNs$r3]$1$k!%(B
/*!
  \param m	$B3]$1$k9TNs(B
  \return	$B$3$N9TNs!$$9$J$o$A(B
		\f$\TUvec{A}{}\leftarrow \TUvec{A}{}\TUvec{M}{}\f$
*/
template <class T> template <class T2> inline Matrix<T>&
Matrix<T>::operator *=(const Matrix<T2>& m)
{
    return *this = *this * m;
}

//! $B$3$N9TNs$NId9f$rH?E>$7$?9TNs$rJV$9!%(B
/*!
  \return	$BId9f$rH?E>$7$?9TNs!$$9$J$o$A(B\f$-\TUvec{A}{}\f$
*/
template <class T> inline Matrix<T>
Matrix<T>::operator -() const
{
    return Matrix(*this) *= -1;
}

//! $B$3$N9TNs$N5U9TNs$rJV$9!%(B
/*!
  \return	$B5U9TNs!$$9$J$o$A(B\f$\TUinv{A}{}\f$
*/
template <class T> inline Matrix<T>
Matrix<T>::inv() const
{
    return I(nrow()).solve(*this);
}

//! $B$3$N9TNs$N(B2$B>h%N%k%`$rJV$9!%(B
/*!
  \return	$B9TNs$N(B2$B>h%N%k%`!$$9$J$o$A(B\f$\TUnorm{\TUvec{A}{}}\f$
*/
template <class T> inline T
Matrix<T>::length() const
{
    return sqrt(square());
}

//! $BC10L@5J}9TNs$r@8@.$9$k!%(B
/*!
  \param d	$BC10L@5J}9TNs$N<!85(B
  \return	$BC10L@5J}9TNs(B
*/
template <class T> inline Matrix<T>
Matrix<T>::I(u_int d)
{
    return Matrix<T>(d, d).diag(1.0);
}

//! 3$B<!852sE>9TNs$r@8@.$9$k!%(B
/*!
  \param n	$B2sE><4$rI=$9(B3$B<!85C10L%Y%/%H%k(B
  \param c	$B2sE>3Q$N(Bcos$BCM(B
  \param s	$B2sE>3Q$N(Bsin$BCM(B
  \return	$B@8@.$5$l$?2sE>9TNs!$$9$J$o$A(B
		\f[
		  \TUtvec{R}{} \equiv \TUvec{I}{3}\cos\theta
		  + \TUvec{n}{}\TUtvec{n}{}(1 - \cos\theta)
		  - \TUskew{n}{}\sin\theta
		\f]
*/
template <class T> template <class T2, class B2> Matrix<T>
Matrix<T>::Rt(const Vector<T2, B2>& n, T c, T s)
{
    Matrix<T>	Qt = n % n;
    Qt *= (1.0 - c);
    Qt[0][0] += c;
    Qt[1][1] += c;
    Qt[2][2] += c;
    Qt[0][1] += n[2] * s;
    Qt[0][2] -= n[1] * s;
    Qt[1][0] -= n[2] * s;
    Qt[1][2] += n[0] * s;
    Qt[2][0] += n[1] * s;
    Qt[2][1] -= n[0] * s;

    return Qt;
}

//! 3$B<!852sE>9TNs$r@8@.$9$k!%(B
/*!
  \param axis	$B2sE>3Q$H2sE><4$rI=$9(B3$B<!85%Y%/%H%k(B
  \return	$B@8@.$5$l$?2sE>9TNs!$$9$J$o$A(B
		\f[
		  \TUtvec{R}{} \equiv \TUvec{I}{3}\cos\theta
		  + \TUvec{n}{}\TUtvec{n}{}(1 - \cos\theta)
		  - \TUskew{n}{}\sin\theta,{\hskip 1em}\mbox{where}{\hskip 0.5em}
		  \theta = \TUnorm{\TUvec{a}{}},~
		  \TUvec{n}{} = \frac{\TUvec{a}{}}{\TUnorm{\TUvec{a}{}}}
		\f]
*/
template <class T> template <class T2, class B2> Matrix<T>
Matrix<T>::Rt(const Vector<T2, B2>& axis)
{
    const T	theta = axis.length();
    if (theta + 1.0 == 1.0)		// theta << 1 ?
	return I(3);
    else
    {
	T	c = cos(theta), s = sin(theta);
	return Rt(axis / theta, c, s);
    }
}

//! $B9TNs$N%5%$%:$rJQ99$7!$(B0$B$K=i4|2=$9$k!%(B
/*!
  \param r	$B?7$7$$9T?t(B
  \param c	$B?7$7$$Ns?t(B
*/
template <class T> inline void
Matrix<T>::resize(u_int r, u_int c)
{
    Array2<Vector<T> >::resize(r, c);
    *this = 0;
}

//! $B9TNs$NFbIt5-21NN0h$H%5%$%:$rJQ99$9$k!%(B
/*!
  \param p	$B?7$7$$FbIt5-21NN0h$X$N%]%$%s%?(B
  \param r	$B?7$7$$9T?t(B
  \param c	$B?7$7$$Ns?t(B
*/
template <class T> inline void
Matrix<T>::resize(T* p, u_int r, u_int c)
{
    Array2<Vector<T> >::resize(p, r, c);
}

/************************************************************************
*  numerical operators							*
************************************************************************/
//! 2$B$D$N%Y%/%H%k$NB-$7;;(B
/*!
  \param v	$BBh(B1$B0z?t(B
  \param w	$BBh(B2$B0z?t(B
  \return	$B7k2L$r3JG<$7$?%Y%/%H%k!$$9$J$o$A(B\f$\TUvec{v}{}+\TUvec{w}{}\f$
*/
template <class T1, class B1, class T2, class B2> inline Vector<T1, B1>
operator +(const Vector<T1, B1>& v, const Vector<T2, B2>& w)
{
    return Vector<T1, B1>(v) += w;
}

//! 2$B$D$N%Y%/%H%k$N0z$-;;(B
/*!
  \param v	$BBh(B1$B0z?t(B
  \param w	$BBh(B2$B0z?t(B
  \return	$B7k2L$r3JG<$7$?%Y%/%H%k!$$9$J$o$A(B\f$\TUvec{v}{}-\TUvec{w}{}\f$
*/
template <class T1, class B1, class T2, class B2> inline Vector<T1, B1>
operator -(const Vector<T1, B1>& v, const Vector<T2, B2>& w)
{
    return Vector<T1, B1>(v) -= w;
}

//! $B%Y%/%H%k$KDj?t$r3]$1$k!%(B
/*!
  \param c	$B3]$1$kDj?t(B
  \param v	$B%Y%/%H%k(B
  \return	$B7k2L$r3JG<$7$?%Y%/%H%k!$$9$J$o$A(B\f$c\TUvec{v}{}\f$
*/
template <class T, class B> inline Vector<T, B>
operator *(double c, const Vector<T, B>& v)
{
    return Vector<T, B>(v) *= c;
}

//! $B%Y%/%H%k$KDj?t$r3]$1$k!%(B
/*!
  \param v	$B%Y%/%H%k(B
  \param c	$B3]$1$kDj?t(B
  \return	$B7k2L$r3JG<$7$?%Y%/%H%k!$$9$J$o$A(B\f$c\TUvec{v}{}\f$
*/
template <class T, class B> inline Vector<T, B>
operator *(const Vector<T, B>& v, double c)
{
    return Vector<T, B>(v) *= c;
}

//! $B%Y%/%H%k$N3FMWAG$rDj?t$G3d$k!%(B
/*!
  \param v	$B%Y%/%H%k(B
  \param c	$B3d$kDj?t(B
  \return	$B7k2L$r3JG<$7$?%Y%/%H%k!$$9$J$o$A(B\f$\frac{1}{c}\TUvec{v}{}\f$
*/
template <class T, class B> inline Vector<T, B>
operator /(const Vector<T, B>& v, double c)
{
    return Vector<T, B>(v) /= c;
}

//! 2$B$D$N9TNs$NB-$7;;(B
/*!
  \param m	$BBh(B1$B0z?t(B
  \param n	$BBh(B2$B0z?t(B
  \return	$B7k2L$r3JG<$7$?9TNs!$$9$J$o$A(B\f$\TUvec{M}{}+\TUvec{N}{}\f$
*/
template <class T1, class T2> inline Matrix<T1>
operator +(const Matrix<T1>& m, const Matrix<T2>& n)
{
    return Matrix<T1>(m) += n;
}

//! 2$B$D$N9TNs$N0z$-;;(B
/*!
  \param m	$BBh(B1$B0z?t(B
  \param n	$BBh(B2$B0z?t(B
  \return	$B7k2L$r3JG<$7$?9TNs!$$9$J$o$A(B\f$\TUvec{M}{}-\TUvec{N}{}\f$
*/
template <class T1, class T2> inline Matrix<T1>
operator -(const Matrix<T1>& m, const Matrix<T2>& n)
{
    return Matrix<T1>(m) -= n;
}

//! $B9TNs$KDj?t$r3]$1$k!%(B
/*!
  \param c	$B3]$1$kDj?t(B
  \param m	$B9TNs(B
  \return	$B7k2L$r3JG<$7$?9TNs!$$9$J$o$A(B\f$c\TUvec{M}{}\f$
*/
template <class T> inline Matrix<T>
operator *(double c, const Matrix<T>& m)
{
    return Matrix<T>(m) *= c;
}

//! $B9TNs$KDj?t$r3]$1$k!%(B
/*!
  \param m	$B9TNs(B
  \param c	$B3]$1$kDj?t(B
  \return	$B7k2L$r3JG<$7$?9TNs!$$9$J$o$A(B\f$c\TUvec{M}{}\f$
*/
template <class T> inline Matrix<T>
operator *(const Matrix<T>& m, double c)
{
    return Matrix<T>(m) *= c;
}

//! $B9TNs$N3FMWAG$rDj?t$G3d$k!%(B
/*!
  \param m	$B9TNs(B
  \param c	$B3d$kDj?t(B
  \return	$B7k2L$r3JG<$7$?9TNs!$$9$J$o$A(B\f$\frac{1}{c}\TUvec{M}{}\f$
*/
template <class T> inline Matrix<T>
operator /(const Matrix<T>& m, double c)
{
    return Matrix<T>(m) /= c;
}

//! 2$B$D$N(B3$B<!85%Y%/%H%k$N%Y%/%H%k@Q(B
/*!
  \param v	$BBh(B1$B0z?t(B
  \param w	$BBh(B2$B0z?t(B
  \return	$B%Y%/%H%k@Q!$$9$J$o$A(B\f$\TUvec{v}{}\times\TUvec{w}{}\f$
*/
template <class T1, class B1, class T2, class B2> inline Vector<T1, B1>
operator ^(const Vector<T1, B1>& v, const Vector<T2, B2>& w)
{
    return Vector<T1, B1>(v) ^= w;
}

//! 2$B$D$N%Y%/%H%k$NFb@Q(B
/*!
  \param v	$BBh(B1$B0z?t(B
  \param w	$BBh(B2$B0z?t(B
  \return	$BFb@Q!$$9$J$o$A(B\f$\TUtvec{v}{}\TUvec{w}{}\f$
*/
template <class T1, class B1, class T2, class B2> T1
operator *(const Vector<T1, B1>& v, const Vector<T2, B2>& w)
{
    v.check_dim(w.dim());
    T1	val = 0;
    for (int i = 0; i < v.dim(); ++i)
	val += v[i] * w[i];
    return val;
}

//! $B%Y%/%H%k$H9TNs$N@Q(B
/*!
  \param v	$B%Y%/%H%k(B
  \param m	$B9TNs(B
  \return	$B7k2L$N%Y%/%H%k!$$9$J$o$A(B\f$\TUtvec{v}{}\TUvec{M}{}\f$
*/
template <class T1, class B1, class T2> Vector<T1, B1>
operator *(const Vector<T1, B1>& v, const Matrix<T2>& m)
{
    v.check_dim(m.nrow());
    Vector<T1, B1> val(m.ncol());
    for (int j = 0; j < m.ncol(); ++j)
	for (int i = 0; i < m.nrow(); ++i)
	    val[j] += v[i] * m[i][j];
    return val;
}

//! 2$B$D$N%Y%/%H%k$N30@Q(B
/*!
  \param v	$BBh(B1$B0z?t(B
  \param w	$BBh(B2$B0z?t(B
  \return	$B7k2L$N9TNs!$$9$J$o$A(B\f$\TUvec{v}{}\TUtvec{w}{}\f$
*/
template <class T1, class B1, class T2, class B2> Matrix<T1>
operator %(const Vector<T1, B1>& v, const Vector<T2, B2>& w)
{
    Matrix<T1>	val(v.dim(), w.dim());
    for (int i = 0; i < v.dim(); ++i)
	for (int j = 0; j < w.dim(); ++j)
	    val[i][j] = v[i] * w[j];
    return val;
}

//! 3$B<!85%Y%/%H%k$H(B3x?$B9TNs$N3FNs$H$N%Y%/%H%k@Q(B
/*!
  \param v			3$B<!85%Y%/%H%k(B
  \param m			3x?$B9TNs(B
  \return			$B7k2L$N(B3x?$B9TNs!$$9$J$o$A(B
				\f$\TUvec{v}{}\times\TUvec{M}{}\f$
  \throw std::invalid_argument	v$B$,(B3$B<!85%Y%/%H%k$G$J$$$+(Bm$B$,(B3x?$B9TNs$G$J$$>l9g$K(B
				$BAw=P(B
*/
template <class T, class B, class T2> Matrix<T>
operator ^(const Vector<T, B>& v, const Matrix<T2>& m)
{
    v.check_dim(m.nrow());
    if (v.dim() != 3)
	throw std::invalid_argument("operator ^(const Vecotr<T>&, const Matrix<T>&): dimension of vector must be 3!!");
    Matrix<T>	val(m.nrow(), m.ncol());
    for (int j = 0; j < val.ncol(); ++j)
    {
	val[0][j] = v[1] * m[2][j] - v[2] * m[1][j];
	val[1][j] = v[2] * m[0][j] - v[0] * m[2][j];
	val[2][j] = v[0] * m[1][j] - v[1] * m[0][j];
    }
    return val;
}

//! 2$B$D$N9TNs$N@Q(B
/*!
  \param m	$BBh(B1$B0z?t(B
  \param n	$BBh(B2$B0z?t(B
  \return	$B7k2L$N9TNs!$$9$J$o$A(B\f$\TUvec{M}{}\TUvec{N}{}\f$
*/
template <class T1, class T2> Matrix<T1>
operator *(const Matrix<T1>& m, const Matrix<T2>& n)
{
    n.check_dim(m.ncol());
    Matrix<T1>	val(m.nrow(), n.ncol());
    for (int i = 0; i < m.nrow(); ++i)
	for (int j = 0; j < n.ncol(); ++j)
	    for (int k = 0; k < m.ncol(); ++k)
		val[i][j] += m[i][k] * n[k][j];
    return val;
}

//! $B9TNs$H%Y%/%H%k$N@Q(B
/*!
  \param m	$B9TNs(B
  \param v	$B%Y%/%H%k(B
  \return	$B7k2L$N%Y%/%H%k!$$9$J$o$A(B\f$\TUvec{M}{}\TUvec{v}{}\f$
*/
template <class T, class T2, class B2> Vector<T>
operator *(const Matrix<T>& m, const Vector<T2, B2>& v)
{
    Vector<T>	val(m.nrow());
    for (int i = 0; i < m.nrow(); ++i)
	val[i] = m[i] * v;
    return val;
}

//! ?x3$B9TNs$N3F9T$H(B3$B<!85%Y%/%H%k$N%Y%/%H%k@Q(B
/*!
  \param m	?x3$B9TNs(B
  \param v	3$B<!85%Y%/%H%k(B
  \return	$B7k2L$N9TNs!$$9$J$o$A(B\f$(\TUtvec{M}{}\times\TUvec{v}{})^\top\f$
*/
template <class T, class T2, class B2> inline Matrix<T>
operator ^(const Matrix<T>& m, const Vector<T2, B2>& v)
{
    return Matrix<T>(m) ^= v;
}

/************************************************************************
*  class LUDecomposition<T>						*
************************************************************************/
//! $B@5J}9TNs$N(BLU$BJ,2r$rI=$9%/%i%9(B
template <class T>
class LUDecomposition : private Array2<Vector<T> >
{
  public:
    LUDecomposition(const Matrix<T>&)			;

    template <class T2, class B2>
    void	substitute(Vector<T2, B2>&)	const	;

  //! $B$b$H$N@5J}9TNs$N9TNs<0$rJV$9!%(B
  /*!
    \return	$B$b$H$N@5J}9TNs$N9TNs<0(B
  */
    T		det()				const	{return _det;}
    
  private:
    using	Array2<Vector<T> >::nrow;
    using	Array2<Vector<T> >::ncol;
    
    Array<int>	_index;
    T		_det;
};

//! $B$b$H$N@5J}9TNs$r78?t9TNs$H$7$?O"N)(B1$B<!J}Dx<0$r2r$/!%(B
/*!
  \param b			$B$b$H$N@5J}9TNs(B\f$\TUvec{M}{}\f$$B$HF1$8<!(B
				$B85$r;}$D%Y%/%H%k!%(B\f$\TUtvec{b}{} =
				\TUtvec{x}{}\TUvec{M}{}\f$$B$N2r$KJQ49$5(B
				$B$l$k!%(B
  \throw std::invalid_argument	$B%Y%/%H%k(Bb$B$N<!85$,$b$H$N@5J}9TNs$N<!85$K0lCW(B
				$B$7$J$$>l9g$KAw=P(B
  \throw std::runtime_error	$B$b$H$N@5J}9TNs$,@5B'$G$J$$>l9g$KAw=P(B
*/
template <class T> template <class T2, class B2> void
LUDecomposition<T>::substitute(Vector<T2, B2>& b) const
{
    if (b.dim() != ncol())
	throw std::invalid_argument("TU::LUDecomposition<T>::substitute: Dimension of given vector is not equal to mine!!");
    
    Vector<T>	tmp(b);
    for (int j = 0; j < b.dim(); ++j)
	b[j] = tmp[_index[j]];

    for (int j = 0; j < b.dim(); ++j)		// forward substitution
	for (int i = 0; i < j; ++i)
	    b[j] -= b[i] * (*this)[i][j];
    for (int j = b.dim(); --j >= 0; )		// backward substitution
    {
	for (int i = b.dim(); --i > j; )
	    b[j] -= b[i] * (*this)[i][j];
	if ((*this)[j][j] == 0.0)		// singular matrix ?
	    throw std::runtime_error("TU::LUDecomposition<T>::substitute: singular matrix !!");
	b[j] /= (*this)[j][j];
    }
}

//! $BO"N)(B1$B<!J}Dx<0$r2r$/!%(B
/*!
  \param m	$B@5B'$J@5J}9TNs(B
  \return	\f$\TUtvec{u}{} = \TUtvec{x}{}\TUvec{M}{}\f$
		$B$N2r$rG<$a$?$3$N%Y%/%H%k!$$9$J$o$A(B
		\f$\TUtvec{u}{} \leftarrow \TUtvec{u}{}\TUinv{M}{}\f$
*/
template <class T, class B> template <class T2> inline Vector<T, B>&
Vector<T, B>::solve(const Matrix<T2>& m)
{
    LUDecomposition<T>(m).substitute(*this);
    return *this;
}

//! $BO"N)(B1$B<!J}Dx<0$r2r$/!%(B
/*!
  \param m	$B@5B'$J@5J}9TNs(B
  \return	\f$\TUvec{A}{} = \TUvec{X}{}\TUvec{M}{}\f$
		$B$N2r$rG<$a$?$3$N9TNs!$$9$J$o$A(B
		\f$\TUvec{A}{} \leftarrow \TUvec{A}{}\TUinv{M}{}\f$
*/
template <class T> template <class T2> Matrix<T>&
Matrix<T>::solve(const Matrix<T2>& m)
{
    LUDecomposition<T>	lu(m);
    
    for (int i = 0; i < nrow(); ++i)
	lu.substitute((*this)[i]);
    return *this;
}

//! $B$3$N9TNs$N9TNs<0$rJV$9!%(B
/*!
  \return	$B9TNs<0!$$9$J$o$A(B\f$\det\TUvec{A}{}\f$
*/
template <class T> inline T
Matrix<T>::det() const
{
    return LUDecomposition<T>(*this).det();
}

/************************************************************************
*  class Householder<T>							*
************************************************************************/
template <class T>	class QRDecomposition;
template <class T>	class TriDiagonal;
template <class T>	class BiDiagonal;

//! Householder$BJQ49$rI=$9%/%i%9(B
template <class T>
class Householder : public Matrix<T>
{
  private:
    Householder(u_int dd, u_int d)
	:Matrix<T>(dd, dd), _d(d), _sigma(Matrix<T>::nrow())	{}
    Householder(const Matrix<T>&, u_int)			;

    using		Matrix<T>::dim;
    
    void		apply_from_left(Matrix<T>&, int)	;
    void		apply_from_right(Matrix<T>&, int)	;
    void		apply_from_both(Matrix<T>&, int)	;
    void		make_transformation()			;
    const Vector<T>&	sigma()			const	{return _sigma;}
    Vector<T>&		sigma()				{return _sigma;}
    bool		sigma_is_zero(int, T)	const	;

  private:
    const u_int		_d;		// deviation from diagonal element
    Vector<T>		_sigma;

    friend class	QRDecomposition<T>;
    friend class	TriDiagonal<T>;
    friend class	BiDiagonal<T>;
};

/************************************************************************
*  class QRDecomposition<T>						*
************************************************************************/
//! $B0lHL9TNs$N(BQR$BJ,2r$rI=$9%/%i%9(B
/*!
  $BM?$($i$l$?9TNs(B\f$\TUvec{A}{} \in \TUspace{R}{m\times n}\f$$B$KBP$7$F(B
  \f$\TUvec{A}{} = \TUtvec{R}{}\TUtvec{Q}{}\f$$B$J$k2<H>;03Q9TNs(B
  \f$\TUtvec{R}{} \in \TUspace{R}{m\times n}\f$$B$H2sE>9TNs(B
  \f$\TUtvec{Q}{} \in \TUspace{R}{n\times n}\f$$B$r5a$a$k(B
  $B!J(B\f$\TUvec{A}{}\f$$B$N3F9T$r(B\f$\TUtvec{Q}{}\f$$B$N9T$N@~7?7k9g$GI=8=$9(B
  $B$k!K!%(B
 */
template <class T>
class QRDecomposition : private Matrix<T>
{
  public:
    QRDecomposition(const Matrix<T>&)			;

  //! QR$BJ,2r$N2<H>;03Q9TNs$rJV$9!%(B
  /*!
    \return	$B2<H>;03Q9TNs(B\f$\TUtvec{R}{}\f$
  */
    const Matrix<T>&	Rt()			const	{return *this;}

  //! QR$BJ,2r$N2sE>9TNs$rJV$9!%(B
  /*!
    \return	$B2sE>9TNs(B\f$\TUtvec{Q}{}\f$
  */
    const Matrix<T>&	Qt()			const	{return _Qt;}
    
  private:
    using		Matrix<T>::nrow;
    using		Matrix<T>::ncol;
    
    Householder<T>	_Qt;			// rotation matrix
};

/************************************************************************
*  class TriDiagonal<T>							*
************************************************************************/
//! $BBP>N9TNs$N(B3$B=EBP3Q2=$rI=$9%/%i%9(B
/*!
  $BM?$($i$l$?BP>N9TNs(B\f$\TUvec{A}{} \in \TUspace{R}{d\times d}\f$$B$KBP$7(B
  $B$F(B\f$\TUtvec{U}{}\TUvec{A}{}\TUvec{U}{}\f$$B$,(B3$B=EBP3Q9TNs$H$J$k$h$&$J2s(B
  $BE>9TNs(B\f$\TUtvec{U}{} \in \TUspace{R}{d\times d}\f$$B$r5a$a$k!%(B
 */
template <class T>
class TriDiagonal
{
  public:
    TriDiagonal(const Matrix<T>&)			;

  //! 3$B=EBP3Q2=$5$l$kBP>N9TNs$N<!85(B(= $B9T?t(B = $BNs?t(B)$B$rJV$9!%(B
  /*!
    \return	$BBP>N9TNs$N<!85(B
  */
    u_int		dim()			const	{return _Ut.nrow();}

  //! 3$B=EBP3Q2=$r9T$&2sE>9TNs$rJV$9!%(B
  /*!
    \return	$B2sE>9TNs(B
  */
    const Matrix<T>&	Ut()			const	{return _Ut;}

  //! 3$B=EBP3Q9TNs$NBP3Q@.J,$rJV$9!%(B
  /*!
    \return	$BBP3Q@.J,(B
  */
    const Vector<T>&	diagonal()		const	{return _diagonal;}

  //! 3$B=EBP3Q9TNs$NHsBP3Q@.J,$rJV$9!%(B
  /*!
    \return	$BHsBP3Q@.J,(B
  */
    const Vector<T>&	off_diagonal()		const	{return _Ut.sigma();}

    void		diagonalize()			;
    
  private:
    enum		{NITER_MAX = 30};

    bool		off_diagonal_is_zero(int)		const	;
    void		initialize_rotation(int, int,
					    T&, T&)	const	;
    
    Householder<T>	_Ut;
    Vector<T>		_diagonal;
    Vector<T>&		_off_diagonal;
};

/************************************************************************
*  class BiDiagonal<T>							*
************************************************************************/
//! $B0lHL9TNs$N(B2$B=EBP3Q2=$rI=$9%/%i%9(B
/*!
  $BM?$($i$l$?0lHL9TNs(B\f$\TUvec{A}{} \in \TUspace{R}{m\times n}\f$$B$KBP$7(B
  $B$F(B\f$\TUtvec{V}{}\TUvec{A}{}\TUvec{U}{}\f$$B$,(B2$B=EBP3Q9TNs$H$J$k$h$&$J(B2
  $B$D$N2sE>9TNs(B\f$\TUtvec{U}{} \in \TUspace{R}{n\times n}\f$,
  \f$\TUtvec{V}{} \in \TUspace{R}{m\times m}\f$$B$r5a$a$k!%(B\f$m \le n\f$
  $B$N>l9g$O2<H>;03Q$J(B2$B=EBP3Q9TNs$K!$(B\f$m > n\f$$B$N>l9g$O>eH>;03Q$J(B2$B=EBP3Q(B
  $B9TNs$K$J$k!%(B
 */
template <class T>
class BiDiagonal
{
  public:
    BiDiagonal(const Matrix<T>&)		;

  //! 2$B=EBP3Q2=$5$l$k9TNs$N9T?t$rJV$9!%(B
  /*!
    \return	$B9TNs$N9T?t(B
  */
    u_int		nrow()		const	{return _Vt.nrow();}

  //! 2$B=EBP3Q2=$5$l$k9TNs$NNs?t$rJV$9!%(B
  /*!
    \return	$B9TNs$NNs?t(B
  */
    u_int		ncol()		const	{return _Ut.nrow();}

  //! 2$B=EBP3Q2=$r9T$&$?$a$K1&$+$i3]$1$k2sE>9TNs$NE>CV$rJV$9!%(B
  /*!
    \return	$B1&$+$i3]$1$k2sE>9TNs$NE>CV(B
  */
    const Matrix<T>&	Ut()		const	{return _Ut;}

  //! 2$B=EBP3Q2=$r9T$&$?$a$K:8$+$i3]$1$k2sE>9TNs$rJV$9!%(B
  /*!
    \return	$B:8$+$i3]$1$k2sE>9TNs(B
  */
    const Matrix<T>&	Vt()		const	{return _Vt;}

  //! 2$B=EBP3Q9TNs$NBP3Q@.J,$rJV$9!%(B
  /*!
    \return	$BBP3Q@.J,(B
  */
    const Vector<T>&	diagonal()	const	{return _Dt.sigma();}

  //! 2$B=EBP3Q9TNs$NHsBP3Q@.J,$rJV$9!%(B
  /*!
    \return	$BHsBP3Q@.J,(B
  */
    const Vector<T>&	off_diagonal()	const	{return _Et.sigma();}

    void		diagonalize()		;

  private:
    enum		{NITER_MAX = 30};
    
    bool		diagonal_is_zero(int)			const	;
    bool		off_diagonal_is_zero(int)		const	;
    void		initialize_rotation(int, int,
					    T&, T&)	const	;

    Householder<T>	_Dt;
    Householder<T>	_Et;
    Vector<T>&		_diagonal;
    Vector<T>&		_off_diagonal;
    T			_anorm;
    const Matrix<T>&	_Ut;
    const Matrix<T>&	_Vt;
};

/************************************************************************
*  class SVDecomposition<T>						*
************************************************************************/
//! $B0lHL9TNs$NFC0[CMJ,2r$rI=$9%/%i%9(B
/*!
  $BM?$($i$l$?0lHL9TNs(B\f$\TUvec{A}{} \in \TUspace{R}{m\times n}\f$$B$KBP$7(B
  $B$F(B\f$\TUtvec{V}{}\TUvec{A}{}\TUvec{U}{}\f$$B$,BP3Q9TNs$H$J$k$h$&$J(B2$B$D$N(B
  $B2sE>9TNs(B\f$\TUtvec{U}{} \in \TUspace{R}{n\times n}\f$,
  \f$\TUtvec{V}{} \in \TUspace{R}{m\times m}\f$$B$r5a$a$k!%(B
 */
template <class T>
class SVDecomposition : private BiDiagonal<T>
{
  public:
  //! $BM?$($i$l$?0lHL9TNs$NFC0[CMJ,2r$r5a$a$k!%(B
  /*!
    \param a	$BFC0[CMJ,2r$9$k0lHL9TNs(B
  */
    SVDecomposition(const Matrix<T>& a)
	:BiDiagonal<T>(a)			{BiDiagonal<T>::diagonalize();}

    using	BiDiagonal<T>::nrow;
    using	BiDiagonal<T>::ncol;
    using	BiDiagonal<T>::Ut;
    using	BiDiagonal<T>::Vt;
    using	BiDiagonal<T>::diagonal;

  //! $BFC0[CM$r5a$a$k!%(B
  /*!
    \param i	$B@dBPCM$NBg$-$$=g$KJB$s$@FC0[CM$N(B1$B$D$r;XDj$9$k(Bindex
    \return	$B;XDj$5$l$?(Bindex$B$KBP1~$9$kFC0[CM(B
  */
    const T&	operator [](int i)	const	{return diagonal()[i];}
};

/************************************************************************
*  typedefs								*
************************************************************************/
typedef Vector<short,  FixedSizedBuf<short,  2> >	Vector2s;
typedef Vector<int,    FixedSizedBuf<int,    2> >	Vector2i;
typedef Vector<float,  FixedSizedBuf<float,  2> >	Vector2f;
typedef Vector<double, FixedSizedBuf<double, 2> >	Vector2d;
typedef Vector<short,  FixedSizedBuf<short,  3> >	Vector3s;
typedef Vector<int,    FixedSizedBuf<int,    3> >	Vector3i;
typedef Vector<float,  FixedSizedBuf<float,  3> >	Vector3f;
typedef Vector<double, FixedSizedBuf<double, 3> >	Vector3d;
typedef Vector<short,  FixedSizedBuf<short,  4> >	Vector4s;
typedef Vector<int,    FixedSizedBuf<int,    4> >	Vector4i;
typedef Vector<float,  FixedSizedBuf<float,  4> >	Vector4f;
typedef Vector<double, FixedSizedBuf<double, 4> >	Vector4d;

/************************************************************************
*  class Minimization1<S>						*
************************************************************************/
static const double	DEFAULT_TOL = 3.0e-8;

template <class S>
class Minimization1
{
  private:
    enum		{DEFAULT_NITER_MAX = 100};

  public:
    Minimization1(S tol = DEFAULT_TOL, int niter_max = DEFAULT_NITER_MAX)
	:_tol(tol), _niter_max(niter_max)				{}
    
    virtual S		operator ()(const S&)			const	= 0;
    S			minimize(S&, S)				const	;

  private:
    const S		_tol;
    const int		_niter_max;
};

/************************************************************************
*  class Minimization<S, T>						*
************************************************************************/
template <class S, class T>
class Minimization
{
  private:
    class LineFunction : public Minimization1<S>
    {
      public:
	LineFunction(const Minimization<S, T>& func,
		     const T& x, const Vector<S>& h,
		     S tol, int niter_max)
	  :Minimization1<S>(tol, niter_max),
	   _func(func), _x(x), _h(h)		{}
    
	S	operator ()(const S& d)	const	{return _func(_func.proceed
							      (_x, d * _h));}
    
      private:
	const Minimization<S, T>&	_func;
	const T&			_x;
	const Vector<S>&		_h;
    };

  private:
    enum		{DEFAULT_NITER_MAX = 1000};
		 
  public:
    Minimization(S tol = DEFAULT_TOL, int niter_max = DEFAULT_NITER_MAX,
		 int pr = 0)
      :_tol(tol), _niter_max(niter_max), _print(pr)			{}
    
    virtual S		operator ()(const T&)			const	= 0;
    virtual Vector<S>	ngrad(const T& x)			const	= 0;
    virtual T		proceed(const T&, const Vector<S>&)	const	= 0;
    S			minimize(T&)					;
    S			steepest_descent(T&)				;
    S			line_minimize(T&, const Vector<S>&)	const	;

  protected:
    virtual void	update(const T&)				;
    virtual void	print(int, S, const T&)			const	;
    
  private:
    int			near_enough(S, S)			const	;
 
    const S		_tol;
    const int		_niter_max;
    const int		_print;
};

template <class S, class T> inline int
Minimization<S, T>::near_enough(S a, S b) const
{
#define EPS	1.0e-10
    return 2.0*fabs(a - b) <= _tol*(fabs(a) + fabs(b) + EPS);
}
 
}

#endif	/* !__TUVectorPP_h	*/
