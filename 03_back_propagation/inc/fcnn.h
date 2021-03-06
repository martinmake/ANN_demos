#ifndef _FEED_FORWARD_DEMO_FCNN_H_
#define _FEED_FORWARD_DEMO_FCNN_H_

#include "datatypes.h"
#include "layer.h"

class Fcnn
{
	private:
		uint16_t m_input_count;
		vector m_outputs;
		std::vector<Layer> m_layers;

	public:
		Fcnn(const std::vector<uint16_t>&                architecture,
		     const std::vector<activation_func_t>&       activation_funcs,
		     const std::vector<activation_func_deriv_t>& activation_funcs_derivs);
		~Fcnn();

		vector& forward(const vector& inputs);
		void backward(const vector& target_outputs, const vector& inputs);
		void learn(const vector& target_outputs, const vector& inputs);
		void set_weights(const tensor& weights);
		void set_random_weights();
		void show_weights(uint8_t precision);
};

#endif
