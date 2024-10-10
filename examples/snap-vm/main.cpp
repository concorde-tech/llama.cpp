#include "arg.h"
#include "common.h"
#include "console.h"
#include "llama.h"
#include "log.h"
#include "sampling.h"

#include <cassert>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static llama_context **g_ctx;
static llama_model **g_model;
static gpt_sampler **g_smpl;
static gpt_params *g_params;
static std::vector<llama_token> *g_input_tokens;
static std::ostringstream *g_output_ss;
static std::vector<llama_token> *g_output_tokens;
static bool is_interacting = false;
static bool need_insert_eot = false;

static void print_usage(int argc, char **argv) {
  (void)argc;

  LOG("\nexample usage:\n");
  LOG("\n  text generation:     %s -m your_model.gguf -p \"I believe the "
      "meaning of life is\" -n 128\n",
      argv[0]);
  LOG("\n  chat (conversation): %s -m your_model.gguf -p \"You are a helpful "
      "assistant\" -cnv\n",
      argv[0]);
  LOG("\n");
}

int main(int argc, char **argv) {
  gpt_params params;
  g_params = &params;

  if (!gpt_params_parse(argc, argv, params, LLAMA_EXAMPLE_MAIN, print_usage)) {
    return 1;
  }

  gpt_init();

  auto &sparams = params.sparams;

  llama_model *model = nullptr;
  llama_context *ctx = nullptr;
  gpt_sampler *smpl = nullptr;

  g_model = &model;
  g_ctx = &ctx;
  g_smpl = &smpl;

  llama_init_result llama_init = llama_init_from_gpt_params(params);
}
