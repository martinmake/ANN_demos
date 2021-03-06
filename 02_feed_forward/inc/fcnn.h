#ifndef _FEED_FORWARD_DEMO_FCNN_H_
#define _FEED_FORWARD_DEMO_FCNN_H_

#include "datatypes.h"
#include "layer.h"

class Fcnn
{
	private:
		uint16_t m_input_count;
		std::vector<Layer> m_layers;
		bool m_softmax_outputs;

	public:
		Fcnn(const std::vector<uint16_t>& architecture, const std::vector<activation_func_t>& activation_funcs);
		~Fcnn();

		vector compute(const vector& inputs);
		void set_weights(const tensor& weights);
};

#endif
