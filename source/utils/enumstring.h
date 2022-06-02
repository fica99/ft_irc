#pragma once

#include <string>
#include <map>
#include <cassert>

namespace ircserv
{

#define Begin_Enum_String(EnumerationName)                                      \
    template <> struct EnumString<EnumerationName> :                            \
        public EnumStringBase< EnumString<EnumerationName>, EnumerationName >   \
    {                                                                           \
        static void RegisterEnumerators()

#define Enum_String(Enumerator, EnumeratorName)                                             \
            RegisterEnumerator( Enumerator, EnumeratorName );

#define End_Enum_String                                                         \
    }

template <class DerivedType, class EnumType>
class EnumStringBase
{
protected:
    typedef std::map<std::string, EnumType> AssocMap;

protected:
    explicit EnumStringBase();
    ~EnumStringBase();

private:
    EnumStringBase(const EnumStringBase &);
    const EnumStringBase &operator =(const EnumStringBase &);

private:
    static AssocMap &GetMap();

protected:
    static void RegisterEnumerator(const EnumType e, const std::string &eStr);

public:
    static const std::string &From(const EnumType e);

    static bool To(EnumType &e, const std::string &str);
};

template <class EnumType>
struct EnumString : public EnumStringBase< EnumString<EnumType>, EnumType >
{
    static void RegisterEnumerators();
};

template <class D, class E>
typename EnumStringBase<D,E>::AssocMap &EnumStringBase<D,E>::GetMap()
{
    static AssocMap assocMap;
    static bool     bFirstAccess = true;

    if( bFirstAccess )
    {
        bFirstAccess = false;
        D::RegisterEnumerators();
        assert( !assocMap.empty() );
    }

    return assocMap;
}

template <class D, class E>
void EnumStringBase<D,E>::RegisterEnumerator(const E e, const std::string &eStr)
{
    const bool bRegistered = GetMap().insert( typename AssocMap::value_type( eStr, e ) ).second;
    assert( bRegistered );
    (void)sizeof( bRegistered );
}

template <class D, class E>
const std::string &EnumStringBase<D,E>::From(const E e)
{
    for(;;)
    {
        typename AssocMap::const_iterator i;
        for(i = GetMap().begin(); i != GetMap().end(); ++i)
            if( (*i).second == e )
                break;

        if( i == GetMap().end() )
            break;

        typename AssocMap::const_iterator j( i );
        for(++j; j != GetMap().end(); ++j)
            if( (*j).second == e )
                break;

        if( j != GetMap().end() )
            break;

        return (*i).first;
    }

    static const std::string dummy;
    return dummy;
}

template <class D, class E>
bool EnumStringBase<D,E>::To(E &e, const std::string &str)
{
    const typename AssocMap::const_iterator itr( GetMap().find( str ) );

    if( itr != GetMap().end() )
    {
        e = (*itr).second;
        return true;
    }

    return false;
}

}
