/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* SPU based on naehrwert's code */

#include <inttypes.h>
#include <stdint.h>

#define EID_ROOT_KEY_ADDR 0x00
#define EID_ROOT_KEY_SIZE 0x30

#define SHARED_LS_AREA_OFFSET 0x3E000

uint64_t copy_data(void* dst, const void* src, uint64_t size) {
	uint64_t count;
	uint64_t i;
	count = 1 + (size - 1) / sizeof(uint64_t);
	for (i = 0; i < count; ++i)
		*((uint64_t*)dst + i) = *((uint64_t*)src + i);
	return count;
}

int main(void) {
	copy_data((void*)SHARED_LS_AREA_OFFSET, (const void*)EID_ROOT_KEY_ADDR, EID_ROOT_KEY_SIZE);

	while (1) {
	
	}

	return 0;
}
