#ifndef lm_vector_sse_h__
#define lm_vector_sse_h__

#include "lm_vector.h"
#include <intrin.h>


namespace lm {

	template<>
	struct VectorData<float, 4, InstructionSet::SSE2> {
		

		float get(LmSize id) const {
			if (id == 0) {
				return _mm_cvtss_f32(_value);
			}
			else if (id == 1) {
				return _mm_cvtss_f32(_mm_shuffle_ps(_value, _value, _MM_SHUFFLE(1, 1, 1, 1)));
			}
			else if (id == 2) {
				return _mm_cvtss_f32(_mm_shuffle_ps(_value, _value, _MM_SHUFFLE(2, 2, 2, 2)));
			}
			else {
				return _mm_cvtss_f32(_mm_shuffle_ps(_value, _value, _MM_SHUFFLE(3, 3, 3, 3)));
			
			}
		}
		void set(LmSize id, float value) {
			if (id == 0) {
				_value = _mm_move_ss(_value, _mm_set_ss(value));
			}
			else if (id == 1) {
				auto temp = _mm_move_ss(_value, _mm_set_ss(value));
				temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 2, 0, 0));
				_value = _mm_move_ss(temp, _value);
			}
			else if (id == 2) {
				auto temp = _mm_move_ss(_value, _mm_set_ss(value));
				temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 0, 1, 0));
				_value = _mm_move_ss(temp, _value);
			}
			else {
				auto temp = _mm_move_ss(_value, _mm_set_ss(value));
				temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(0, 2, 1, 0));
				_value = _mm_move_ss(temp, _value);
			}
			
		}
	private:
		__m128 _value;
	};

	/*template<typename T, LmSize N>
	struct VectorData<T, N, InstructionSet::SSE2> {
		static_assert(false, "SSE2 vector version is implemented only for Vector4");
	};
	*/
	

	
}

#endif // lm_vector_sse_h__
