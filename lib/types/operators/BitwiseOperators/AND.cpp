#include "../../../../includes/types/JsAny.hpp"

namespace JS {
    int operator&(const JS::Any &any, const JS::Any &other) {
        try {
            switch (any.getValue().index()) {
                case NUMBER:
                    switch (other.getValue().index()) {
                        case NUMBER:
                            return static_cast<int>(std::get<double>(any.getValue())) & static_cast<int>(std::get<double>(any.getValue()));
                        case STRING:
                            return static_cast<int>(std::get<double>(any.getValue())) & static_cast<int>(std::stod(std::get<Rope>(any.getValue()).toString()));
                        case BOOL:
                            return static_cast<int>(std::get<double>(any.getValue())) & static_cast<int>(std::get<bool>(any.getValue()));
                        default:
                            return static_cast<int>(std::get<double>(any.getValue())) & 0;
                    }
                case STRING:
                    switch (any.getValue().index()) {
                        case NUMBER:
                            return static_cast<int>(std::stod(std::get<Rope>(any.getValue()).toString())) & static_cast<int>(std::get<double>(any.getValue()));
                        case STRING:
                            return static_cast<int>(std::stod(std::get<Rope>(any.getValue()).toString())) & static_cast<int>(std::stod(std::get<Rope>(any.getValue()).toString()));
                        case BOOL:
                            return static_cast<int>(std::stod(std::get<Rope>(any.getValue()).toString())) & static_cast<int>(std::get<bool>(any.getValue()));
                        default:
                            return static_cast<int>(std::stod(std::get<Rope>(any.getValue()).toString())) & 0;
                    }
                case BOOL:
                    switch (any.getValue().index()) {
                        case NUMBER:
                            return static_cast<int>(std::get<bool>(any.getValue())) & static_cast<int>(std::get<double>(any.getValue()));
                        case STRING:
                            return static_cast<int>(std::get<bool>(any.getValue())) & static_cast<int>(std::stod(std::get<Rope>(any.getValue()).toString()));
                        case BOOL:
                            return static_cast<int>(std::get<bool>(any.getValue())) & static_cast<int>(std::get<bool>(any.getValue()));
                        default:
                            return static_cast<int>(std::get<bool>(any.getValue())) & 0;
                    }
    /*            case FUNCTION:
                    switch (any.getValue().index()) {
                        case NUMBER:
                            return 0 & std::get<double>(any.getValue());
                        case STRING:
                            return 0 & std::get<double>(std::get<Rope>(any.getValue()).toString());
                        case BOOL:
                            return 0 & std::get<bool>(any.getValue());
                        default:
                            return 0 & 0;
                    }
                case NULL_TYPE:
                    switch (any.getValue().index()) {
                        case NUMBER:
                            return 0 & std::get<double>(any.getValue());
                        case STRING:
                            return 0 & std::get<double>(std::get<Rope>(any.getValue()).toString());
                        case BOOL:
                            return 0 & std::get<bool>(any.getValue());
                        default:
                            return 0 & 0;
                    }
                case UNDEFINED:
                    switch (any.getValue().index()) {
                        case NUMBER:
                            return 0 & std::get<double>(any.getValue());
                        case STRING:
                            return 0 & std::get<double>(std::get<Rope>(any.getValue()).toString());
                        case BOOL:
                            return 0 & std::get<bool>(any.getValue());
                        default:
                            return 0 & 0;

                    }*/
            }
        } catch (std::invalid_argument& e) {
            return 0;
        }
        return 0;
    }
}
