#ifndef _FEED_FORWARD_DEMO_LAYER_H_
#define _FEED_FORWARD_DEMO_LAYER_H_

#include "datatypes.h"

class Layer
{
	private:
		uint16_t m_input_count;
		uint16_t m_output_count;
		matrix   m_weights;
		vector   m_inputs;
		vector   m_outputs;
		activation_func_t       m_activation_func;
		activation_func_deriv_t m_activation_func_deriv;

	public:
		Layer(uint16_t                input_count,
		      uint16_t                output_count,
		      activation_func_t       activation_func,
		      activation_func_deriv_t activation_func_deriv);
		~Layer();

		vector& forward(const vector& inputs);
		vector& backward(const vector& inputs);
		void set_weights(const matrix& weights);
		void set_random_weights();
		inline void show_weights(uint8_t precision) { show_data(m_weights, precision); }

	private:
		inline float generate_random_weight();
};

#endif
