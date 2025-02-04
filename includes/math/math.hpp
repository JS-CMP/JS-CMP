#ifndef JS_CMP_MATH_HPP
#define JS_CMP_MATH_HPP

#include <vector>
#include "../includes/types/Types.hpp"
#include "../includes/utils/Convert.hpp"

/**
 * @class Math
 * @brief Fournit des fonctions mathématiques similaires à l'objet Math de JavaScript.
 *
 * La classe Math offre un ensemble de méthodes statiques qui imitent le comportement de l'objet Math en JavaScript.
 * Chaque fonction accepte un vecteur d'arguments de type JS::Any pour simuler le typage dynamique de JavaScript.
 * Les méthodes implémentent des opérations mathématiques telles que les fonctions trigonométriques, l'exponentiation,
 * le logarithme, l'arrondi, et la génération de nombres aléatoires.
 */
class Math {
public:
    /**
     * @brief Renvoie la valeur absolue du nombre donné.
     * @param args Vecteur contenant un seul élément JS::Any représentant le nombre.
     * @return JS::Any contenant la valeur absolue.
     */
    static JS::Any abs(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie l'arc cosinus (en radians) du nombre donné.
     * @param args Vecteur contenant un seul élément JS::Any représentant le nombre.
     * @return JS::Any contenant l'arc cosinus.
     */
    static JS::Any acos(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie l'arc sinus (en radians) du nombre donné.
     * @param args Vecteur contenant un seul élément JS::Any représentant le nombre.
     * @return JS::Any contenant l'arc sinus.
     */
    static JS::Any asin(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie l'arc tangente (en radians) du nombre donné.
     * @param args Vecteur contenant un seul élément JS::Any représentant le nombre.
     * @return JS::Any contenant l'arc tangente.
     */
    static JS::Any atan(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie une approximation de l'arc tangente du quotient y/x.
     *
     * Le premier argument est interprété comme y et le second comme x. Les signes de y et x sont utilisés
     * pour déterminer le quadrant du résultat. La valeur renvoyée est en radians et se situe dans l'intervalle [-π, +π].
     *
     * @param args Vecteur contenant deux éléments JS::Any : [y, x].
     * @return JS::Any contenant le résultat.
     */
    static JS::Any atan2(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie le plus petit entier supérieur ou égal au nombre donné.
     * @param args Vecteur contenant un seul élément JS::Any représentant le nombre.
     * @return JS::Any contenant la valeur plafond.
     */
    static JS::Any ceil(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie le cosinus de l'angle (en radians) donné.
     * @param args Vecteur contenant un seul élément JS::Any représentant l'angle.
     * @return JS::Any contenant la valeur du cosinus.
     */
    static JS::Any cos(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie l'exponentielle du nombre donné.
     * @param args Vecteur contenant un seul élément JS::Any représentant l'exposant.
     * @return JS::Any contenant e élevé à la puissance du nombre donné.
     */
    static JS::Any exp(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie le plus grand entier inférieur ou égal au nombre donné.
     * @param args Vecteur contenant un seul élément JS::Any représentant le nombre.
     * @return JS::Any contenant la valeur plancher.
     */
    static JS::Any floor(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie le logarithme naturel (base e) du nombre donné.
     * @param args Vecteur contenant un seul élément JS::Any représentant le nombre.
     * @return JS::Any contenant le logarithme.
     */
    static JS::Any log(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie la valeur maximale parmi les arguments donnés.
     * @param args Vecteur de JS::Any représentant les nombres.
     * @return JS::Any contenant la valeur maximale.
     */
    static JS::Any max(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie la valeur minimale parmi les arguments donnés.
     * @param args Vecteur de JS::Any représentant les nombres.
     * @return JS::Any contenant la valeur minimale.
     */
    static JS::Any min(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie le résultat de l'élévation de la base à la puissance de l'exposant.
     * @param args Vecteur contenant deux éléments JS::Any : [base, exposant].
     * @return JS::Any contenant le résultat.
     */
    static JS::Any pow(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie un nombre pseudo-aléatoire dans l'intervalle [0, 1).
     * @param args Vecteur de JS::Any (les arguments sont ignorés).
     * @return JS::Any contenant un nombre pseudo-aléatoire.
     */
    static JS::Any random(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie la valeur du nombre arrondi à l'entier le plus proche.
     * @param args Vecteur contenant un seul élément JS::Any représentant le nombre.
     * @return JS::Any contenant le nombre arrondi.
     */
    static JS::Any round(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie le sinus de l'angle (en radians) donné.
     * @param args Vecteur contenant un seul élément JS::Any représentant l'angle.
     * @return JS::Any contenant la valeur du sinus.
     */
    static JS::Any sin(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie la racine carrée du nombre donné.
     * @param args Vecteur contenant un seul élément JS::Any représentant le nombre.
     * @return JS::Any contenant la racine carrée.
     */
    static JS::Any sqrt(const std::vector<JS::Any>& args);

    /**
     * @brief Renvoie la tangente de l'angle (en radians) donné.
     * @param args Vecteur contenant un seul élément JS::Any représentant l'angle.
     * @return JS::Any contenant la valeur de la tangente.
     */
    static JS::Any tan(const std::vector<JS::Any>& args);

    // Constantes mathématiques accessibles en lecture seule
    constexpr static double E = 2.7182818284590452354;
    constexpr static double LN10 = 2.302585092994046;
    constexpr static double LN2 = 0.6931471805599453;
    constexpr static double LOG2e = 2.302585092994046;
    constexpr static double LOG10E = 0.4342944819032518;
    constexpr static double PI = 3.1415926535897932;
    constexpr static double SQRT1_2 = 0.7071067811865476;
    constexpr static double SQRT2 = 1.4142135623730951;
};

#endif // JS_CMP_MATH_HPP
