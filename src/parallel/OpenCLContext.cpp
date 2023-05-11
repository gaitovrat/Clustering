#include "OpenCLContext.hpp"

#include <CL/cl.h>
#include <CL/opencl.hpp>
#include <iostream>

#include "Utils.hpp"

OpenCLContext::OpenCLContext(const char *filename)
    : m_device(GetDevices()[0]), m_context(m_device),
      m_program(m_context, Utils::readFile(filename)),
      m_queue(m_context, m_device), m_kernels() {
  if (m_program.build() != CL_SUCCESS) {
    std::cerr << "Error building: "
              << m_program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(m_device) << '\n';
  }
}

void OpenCLContext::AddKernel(const char *functionName) {
  m_kernels[functionName] = cl::Kernel(m_program, functionName);
}

cl::Kernel &OpenCLContext::GetKernel(const char *functionName) {
  return m_kernels[functionName];
}

cl::CommandQueue &OpenCLContext::GetQueue() { return m_queue; }

cl::Context &OpenCLContext::GetContext() { return m_context; }

std::vector<cl::Platform> OpenCLContext::GetPlatforms() {
  std::vector<cl::Platform> platforms;
  cl::Platform::get(&platforms);

  return platforms;
}

std::vector<cl::Device> OpenCLContext::GetDevices() {
  std::vector<cl::Device> devices;
  GetPlatforms()[0].getDevices(CL_DEVICE_TYPE_ALL, &devices);
  return devices;
}
