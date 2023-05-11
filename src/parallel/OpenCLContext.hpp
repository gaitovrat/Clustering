#ifndef __OPENCLCONTEXT__
#define __OPENCLCONTEXT__
#include <CL/opencl.hpp>
#include <map>
#include <vector>

class OpenCLContext {
public:
  OpenCLContext(const char *fileName);

  virtual ~OpenCLContext() = default;

  void AddKernel(const char *functionName);

  cl::Kernel &GetKernel(const char *functionName);

  cl::CommandQueue &GetQueue();

  cl::Context& GetContext();

  static std::vector<cl::Platform> GetPlatforms();

  static std::vector<cl::Device> GetDevices();

private:
	cl::Device m_device;
  cl::Context m_context;
  cl::Program m_program;
  cl::CommandQueue m_queue;
  std::map<std::string, cl::Kernel> m_kernels;
};
#endif //__OPENCLCONTEXT__
