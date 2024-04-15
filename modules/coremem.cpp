export module coremem;
export import <memory>;

export {
    template<typename Ty, typename Dx = std::default_delete<Ty>>
    using uniq_ptr = std::unique_ptr<Ty, Dx>;

    template<typename Ty>
    using shr_ptr = std::shared_ptr<Ty>;

    template<typename Ty>
    using handle = std::weak_ptr<Ty>;
}