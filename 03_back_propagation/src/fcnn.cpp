#include <iostream>
#include <stdlib.h>

#include "fcnn.h"
#include "config.h"

Fcnn::Fcnn(const std::vector<uint16_t>&                architecture,
	   const std::vector<activation_func_t>&       activation_funcs,
	   const std::vector<activation_func_deriv_t>& activation_funcs_derivs)
{
	m_input_count = architecture[0];
	for (uint8_t l = 1; l < architecture.size(); l++) {
		m_layers.push_back(Layer(architecture[l-1],
					 architecture[l],
					 activation_funcs[l-1],
					 activation_funcs_derivs[l-1]));
	}

	m_outputs.resize(architecture.back());

	srand(Config::Nn::Weights::Random_generation::seed);
}

Fcnn::~Fcnn()
{
}

vector& Fcnn::forward(const vector& inputs)
{
	m_outputs = inputs;

	for (uint8_t l = 0; l < m_layers.size(); l++)
		m_outputs = m_layers[l].forward(m_outputs);

	return m_outputs;
}

void Fcnn::backward(const vector& target_outputs, const vector& inputs)
{
	forward(inputs);

	vector downstream_gradients;
	m_layers.back().backward_output(target_outputs, downstream_gradients);
	for (uint8_t l = m_layers.size() - 2; l > 0; l--)
		m_layers[l].backward_hidden(downstream_gradients);
	m_layers[0].backward_last(downstream_gradients);
}

void Fcnn::learn(const vector& target_outputs, const vector& inputs)
{
	std::cout << std::endl;
	for (uint16_t epoch = 0; epoch <= Config::Nn::max_epochs; epoch++) {
		backward(target_outputs, inputs);
		if (epoch % 100 == 0) {
			printf("EPOCH: %7u\t\tOUTPUTS: ", epoch);
			show_data(m_outputs, 4);
		}
	}
}

void Fcnn::set_weights(const tensor& weights)
{
	for (uint8_t l = 0; l < m_layers.size(); l++)
		m_layers[l].set_weights(weights[l]);
}

void Fcnn::set_random_weights()
{
	for (uint8_t l = 0; l < m_layers.size(); l++)
		m_layers[l].set_random_weights();
}

void Fcnn::show_weights(uint8_t precision)
{
	m_layers[0].show_weights(precision);
	for (uint8_t l = 1; l < m_layers.size(); l++) {
		std::cout << std::endl;
		m_layers[l].show_weights(precision);
	}
}
