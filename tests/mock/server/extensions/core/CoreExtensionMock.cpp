#include "CoreExtensionMock.h"

namespace Core::Mock {

void CoreExtensionMock::addParamProducer(ParamProducer producer) {
  if (addParamProducer_) addParamProducer_(producer);
}

}  // namespace Core::Mock
