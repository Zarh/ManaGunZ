/*   SCE CONFIDENTIAL                                       */
/*   PlayStation(R)3 Programmer Tool Runtime Library 400.001 */
/*   Copyright (C) 2006 Sony Computer Entertainment Inc.    */
/*   All Rights Reserved.                                   */

#include <stdio.h>
#include <string.h>

#include "cxmlaccess.h"
#include "cxmlutil.h"

using namespace cxml;

// -----------------------------------------------------

bool cxmlutil::CheckElementName( const cxml::Element & elm, const char * valid_name )
{
	const char * name = elm.GetName();

	if( name[0]==valid_name[0] && strcmp(name,valid_name)==0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

cxml::Element cxmlutil::FindChildElement( const cxml::Element & parent, const char * name, const char * idname, const char * idvalue )
{
	cxml::Element child = parent.GetFirstChild();
	cxml::Attribute attr;
	const char * child_id;

	while(child)
	{
		const char * child_name = child.GetName();

		if( child_name[0]==name[0] && strcmp(child_name,name)==0 )
		{
			if( idname && idvalue )
			{
				if( child.GetAttribute( idname, &attr )==RESULT_OK
				 && attr.GetType()==cxml::AttributeType_ID
				 && attr.GetID( &child_id )==RESULT_OK )
				{
					if( child_id[0]==idvalue[0] && strcmp(child_id,idvalue)==0 )
					{
						return child;
					}
				}
			}
			else
			{
				return child;
			}
		}

		child = child.GetNextSibling();
	}
	return cxml::Element();
}

int cxmlutil::FindEmptyAttribute( const cxml::Element & elm, cxml::Attribute * _attr )
{
	int ret;

	cxml::Attribute attr;

	for( int i=0 ; i<elm.NumAttribute() ; i++ )
	{
		ret = elm.GetAttribute(i,&attr);
		if(ret<0)
		{
			return ret;
		}

		if( attr.GetType()==AttributeType_None )
		{
			*_attr = attr;
			return 0;
		}
	}

	return RESULT_ERROR_NOT_EXIST;
}

int cxmlutil::GetInt( const cxml::Element & elm, const char * attrname, int * i )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		return ret;
	}

	ret = attr.GetInt(i);
	if(ret<0)
	{
		return ret;
	}

	return 0;
}

#if CXML_ENABLE_MODIFY
int cxmlutil::SetInt( const cxml::Element & elm, const char * attrname, int i )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		ret = FindEmptyAttribute( elm, &attr );
		if(ret<0)
		{
			return ret;
		}

		ret = attr.SetName(attrname);
		if(ret<0)
		{
			return ret;
		}
	}

	ret = attr.SetInt(i);
	if(ret<0)
	{
		return ret;
	}

	return 0;
}
#endif //CXML_ENABLE_MODIFY

int cxmlutil::GetFloat( const cxml::Element & elm, const char * attrname, float * f )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		return ret;
	}

	ret = attr.GetFloat(f);
	if(ret<0)
	{
		return ret;
	}

	return 0;
}

#if CXML_ENABLE_MODIFY
int cxmlutil::SetFloat( const cxml::Element & elm, const char * attrname, float f )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		ret = FindEmptyAttribute( elm, &attr );
		if(ret<0)
		{
			return ret;
		}

		ret = attr.SetName(attrname);
		if(ret<0)
		{
			return ret;
		}
	}

	ret = attr.SetFloat(f);
	if(ret<0)
	{
		return ret;
	}

	return 0;
}
#endif //CXML_ENABLE_MODIFY

int cxmlutil::GetString( const cxml::Element & elm, const char * attrname, const char ** str, unsigned int * len )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		return ret;
	}

	ret = attr.GetString(str,len);
	if(ret<0)
	{
		return ret;
	}

	return 0;
}

#if CXML_ENABLE_MODIFY
int cxmlutil::SetString( const cxml::Element & elm, const char * attrname, const char * str )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		ret = FindEmptyAttribute( elm, &attr );
		if(ret<0)
		{
			return ret;
		}

		ret = attr.SetName(attrname);
		if(ret<0)
		{
			return ret;
		}
	}

	ret = attr.SetString(str);
	if(ret<0)
	{
		return ret;
	}

	return 0;
}
#endif //CXML_ENABLE_MODIFY

int cxmlutil::GetIntArray( const cxml::Element & elm, const char * attrname, const int ** i, unsigned int * num )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		return ret;
	}

	ret = attr.GetIntArray( i, num );
	if(ret<0)
	{
		return ret;
	}

	return 0;
}

#if CXML_ENABLE_MODIFY
int cxmlutil::SetIntArray( const cxml::Element & elm, const char * attrname, const int * addr, unsigned int num )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		ret = FindEmptyAttribute( elm, &attr );
		if(ret<0)
		{
			return ret;
		}

		ret = attr.SetName(attrname);
		if(ret<0)
		{
			return ret;
		}
	}

	ret = attr.SetIntArray(addr,num);
	if(ret<0)
	{
		return ret;
	}

	return 0;
}
#endif //CXML_ENABLE_MODIFY

int cxmlutil::GetFloatArray( const cxml::Element & elm, const char * attrname, const float ** f, unsigned int * num )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		return ret;
	}

	ret = attr.GetFloatArray( f, num );
	if(ret<0)
	{
		return ret;
	}

	return 0;
}

#if CXML_ENABLE_MODIFY
int cxmlutil::SetFloatArray( const cxml::Element & elm, const char * attrname, const float * addr, unsigned int num )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		ret = FindEmptyAttribute( elm, &attr );
		if(ret<0)
		{
			return ret;
		}

		ret = attr.SetName(attrname);
		if(ret<0)
		{
			return ret;
		}
	}

	ret = attr.SetFloatArray(addr,num);
	if(ret<0)
	{
		return ret;
	}

	return 0;
}
#endif //CXML_ENABLE_MODIFY

int cxmlutil::GetFile( const cxml::Element & elm, const char * attrname, cxml::File * file )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		return ret;
	}

	ret = attr.GetFile( file );
	if(ret<0)
	{
		return ret;
	}

	return 0;
}

#if CXML_ENABLE_MODIFY
int cxmlutil::SetFile( const cxml::Element & elm, const char * attrname, const cxml::File & file )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		ret = FindEmptyAttribute( elm, &attr );
		if(ret<0)
		{
			return ret;
		}

		ret = attr.SetName(attrname);
		if(ret<0)
		{
			return ret;
		}
	}

	ret = attr.SetFile(file);
	if(ret<0)
	{
		return ret;
	}

	return 0;
}
#endif //CXML_ENABLE_MODIFY

int cxmlutil::GetID( const cxml::Element & elm, const char * attrname, const char ** str )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		return ret;
	}

	ret = attr.GetID(str);
	if(ret<0)
	{
		return ret;
	}

	return 0;
}

#if CXML_ENABLE_MODIFY
int cxmlutil::SetID( const cxml::Element & elm, const char * attrname, const char * str )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		ret = FindEmptyAttribute( elm, &attr );
		if(ret<0)
		{
			return ret;
		}

		ret = attr.SetName(attrname);
		if(ret<0)
		{
			return ret;
		}
	}

	ret = attr.SetID(str);
	if(ret<0)
	{
		return ret;
	}

	return 0;
}
#endif //CXML_ENABLE_MODIFY

int cxmlutil::GetIDRef( const cxml::Element & elm, const char * attrname, const char ** str, cxml::Element * entity )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		return ret;
	}

	ret = attr.GetIDRef(str,entity);
	if(ret<0)
	{
		return ret;
	}

	return 0;
}

#if CXML_ENABLE_MODIFY
int cxmlutil::SetIDRef( const cxml::Element & elm, const char * attrname, const char * str )
{
	int ret;
	cxml::Attribute attr;

	ret = elm.GetAttribute( attrname, &attr );
	if(ret<0)
	{
		ret = FindEmptyAttribute( elm, &attr );
		if(ret<0)
		{
			return ret;
		}

		ret = attr.SetName(attrname);
		if(ret<0)
		{
			return ret;
		}
	}

	ret = attr.SetIDRef(str);
	if(ret<0)
	{
		return ret;
	}

	return 0;
}
#endif //CXML_ENABLE_MODIFY
