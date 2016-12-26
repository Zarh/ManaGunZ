
/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

ENTRY(_start)

__self_start = 0x0000000000000000;

SECTIONS
{
	. = __self_start;

	.text :
	{
		*(.text)
		*(.text.*)
		*(.rodata)
		*(.rodata.*)
		*(.gnu.linkonce.t.*)
	}

	.data :
	{
		*(.data)
		*(.data.*)
	}

	.got :
	{
		*(.got)
		*(.got.*)
		__toc_start = .;
		__toc = . + 0x8000;
		*(.toc)
		*(.toc.*)
		__toc_end = .;
	}

	.bss :
	{
		*(.bss)
		*(.bss.*)
	}
	
	__self_end = .;

	.opd :
	{
		*(.opd)
		*(.opd.*)
	}

	
} 
