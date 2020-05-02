#include "Graphics.h"
#include "Shader.h"

int main()
{
  Graphics openGl;
  
  openGl.Init();
  
  openGl.Update();
  
  openGl.Close();

  
  return 0;
}